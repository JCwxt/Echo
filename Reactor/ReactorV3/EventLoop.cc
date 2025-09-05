#include "EventLoop.h"
#include <header.h>

namespace wxt{
EventLoop::EventLoop(Acceptor &acceptor)
:_epfd(createEpollFd())
,_acceptor(acceptor)
,_isLooping(false)
,_evtArr(1024){
    addEpollReadEvent(_acceptor.getFd());
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
            }else{
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
    }

    //将netfd添加到epoll的监听红黑树上
    addEpollReadEvent(netfd);
    //创建TcpConnection对象
    TcpConnectionPtr conn(new TcpConnection(netfd));
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
}
