#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include "Acceptor.h"
#include "TcpConnection.h"
#include "MutexLock.h"
#include <map>
#include <vector>
#include <functional>
using std::map;
using std::vector;
using std::function;

namespace wxt{
class EventLoop{
    using Functor=function<void()>;
public:
    EventLoop(Acceptor &);
    void setAllCallbaks(TcpConnectionCallBack &&cb1,TcpConnectionCallBack  &&cb2,TcpConnectionCallBack &&cb3);
    void loop();
    void unloop(){_isLooping=false;}
    void runInLoop(Functor &&f);//存放任务入Vector,并且唤醒Reactor
private:
    int createEpollFd();
    void addEpollReadEvent(int);
    void delEpollReadEvent(int);
    
    void WaitEpollFd();
    void handleNewConnection();
    void handleMessage(int);

    int  createEventFd();
    void handleReadEvent();
    void wakeup();
    void doPenddingFunctor();//执行任务将数据发送给客户端

private:
    int                             _epfd;
    int                             _eventfd;//用于通知的文件描述符
    Acceptor &                      _acceptor;
    bool                            _isLooping;
    vector<struct epoll_event>      _evtArr;//存放已经就绪的文件描述符以及事件
    map<int,TcpConnectionPtr>       _conns;//存放已经建立好的连接
    
    TcpConnectionCallBack           _onConnection;
    TcpConnectionCallBack           _onMessage;
    TcpConnectionCallBack           _onClose;
    
    vector<Functor>                 _pendings;//存放任务的容器,即待发送的消息
    MutexLock                       _mutex;//存放任务时的互斥锁
};

}

#endif

