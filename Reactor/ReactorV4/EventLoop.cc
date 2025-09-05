#include "EventLoop.h"
#include <header.h>
#include <sys/eventfd.h>
namespace wxt{
EventLoop::EventLoop(Acceptor &acceptor)
:_epfd(createEpollFd())
,_eventfd(createEventFd())
,_acceptor(acceptor)
,_isLooping(false)
,_evtArr(1024)
,_mutex()
{
    //监听建立连接的服务器的文件描述符
    addEpollReadEvent(_acceptor.getFd());
    //监听_eventfd的读事件
    addEpollReadEvent(_eventfd);
}
void EventLoop::setAllCallbaks(TcpConnectionCallBack &&cb1,TcpConnectionCallBack  &&cb2,TcpConnectionCallBack &&cb3){
    //将注册的回调函数转交给TcpConnection对象
    _onConnection=std::move(cb1);
    _onMessage=std::move(cb2);
    _onClose=std::move(cb3);
}
void EventLoop::loop(){
    _isLooping=true;
    while(_isLooping){
        WaitEpollFd();
    }
}

//用来通知IO线程发送消息
//交给TcpConnection对象调用
void EventLoop::runInLoop(Functor &&f){
    _mutex.lock();
    _pendings.push_back(std::move(f));
    _mutex.unlock();

    wakeup();//唤醒epoll,通知线程
}

int EventLoop::createEpollFd(){
    //创建epoll实例
    int epfd=epoll_create1(0);
    if(epfd<0){
        perror("epoll_creat1");
    }
    return epfd;
}

void EventLoop::addEpollReadEvent(int fd){
    //对fd添加读事件监听
    struct epoll_event ev;
    memset(&ev,0,sizeof(ev));
    ev.data.fd=fd;
    ev.events=EPOLLIN;
    int ret=epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&ev);
    if(ret<0){
        perror("epoll_ctl");
    }
}

void EventLoop::delEpollReadEvent(int fd){
    //删除对fd读事件的监听
    struct epoll_event ev;
    memset(&ev,0,sizeof(ev));
    ev.data.fd=fd;
    int ret=epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,&ev);
    if(ret<0){
        perror("epoll_ctl");
    }
}

void EventLoop::WaitEpollFd(){
    int nready=epoll_wait(_epfd,_evtArr.data(),_evtArr.size(),5000);
    if(nready==-1&&errno==EINTR){
        return;
    }else if(nready==-1){
        perror("epoll_wait");
        return;
    }else if(nready==0){
        //超时
        printf("timeout.\n");
    }else{
        for(int i=0;i<nready;++i){
            int fd=_evtArr[i].data.fd;
            if(fd==_acceptor.getFd()){
                //处理新连接
                handleNewConnection();
            }else if(fd==_eventfd){
                //计算线程通知IO线程
                handleReadEvent();
                doPenddingFunctor();
            }
            else{
                //处理已经就绪的连接
                handleMessage(fd);
            }
        }
    }
}

void EventLoop::handleNewConnection(){
    //获取与对端进行交互的文件描述符
    int netfd=_acceptor.accept();
    if(netfd<0){
        perror("netfd");
        return ;
    }

    //将netfd添加到epoll的监听红黑树上
    addEpollReadEvent(netfd);
    //创建TcpConnection对象
    TcpConnectionPtr conn(new TcpConnection(netfd,this));
    //注册函数对象
    conn->setAllCallbacks(_onConnection,_onMessage,_onClose);
    //调用新连接建立的函数对象
    conn->handleNecConnectionCallback();

    //管理conn对象，放入map
    _conns[netfd]=conn;
}


void EventLoop::handleMessage(int fd){
    //查找fd是否存在
    auto it=_conns.find(fd);
    if(it!=_conns.end()){
        //查找成功后，查看连接是否断开
        bool isclosed=it->second->isClosed();
        if(!isclosed){
            //读取客户端发送的数据,调用接收数据的回调函数
            it->second->handleMessageCallback();
        }else{
            //连接断开
            it->second->handleCloseCallback();
            //从监听的红黑树上删除
            delEpollReadEvent(fd);
            //从管理的已经连接的map中移除
            _conns.erase(fd);
        }
    }
}

int EventLoop::createEventFd(){
    int fd=::eventfd(0,0);
    if(fd<0){
        perror("eventfd");
    }
    return fd;
}

void EventLoop::handleReadEvent(){
    uint64_t howmany=0;
    int ret=read(_eventfd,&howmany,sizeof(howmany));
    if(ret!=sizeof(howmany)){
        perror("read");
    }
}

void EventLoop::wakeup(){
    printf("compute thread %ld  wakeup io thread.\n",pthread_self());
    uint64_t one=1;
    int ret=write(_eventfd,&one,sizeof(one));
    if(ret!=sizeof(one)){
        perror("write");
    }
}

void EventLoop::doPenddingFunctor(){
    //执行任务将数据发送给客户端
    printf("io thread %ld:doPenddingFunctor().\n",pthread_self());

    vector<Functor> temp;

    _mutex.lock();
    temp.swap(_pendings);
    _mutex.unlock();

    //经过交换之后，temp中拥有了所有的回调函数
    //遍历temp，进行回调函数的执行
    //执行发送的时候，不会影响_penddingFunctor在计算线程中的使用

    for(auto &f :temp){
        f();
    }
}
}
