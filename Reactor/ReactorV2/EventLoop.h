#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include "Acceptor.h"
#include "TcpConnection.h"
#include <map>
#include <vector>
using std::map;
using std::vector;

namespace wxt{
class EventLoop{
public:
    EventLoop(Acceptor &);
    void setAllCallbaks(TcpConnectionCallBack &&cb1,TcpConnectionCallBack  &&cb2,TcpConnectionCallBack &&cb3);
    void loop();
    int createEpollFd();
    void addEpollReadEvent(int);
    void delEpollReadEvent(int);
    void WaitEpollFd();
    void handleNewConnection();
    void handleMessage(int);
private:
    int                             _epfd;
    Acceptor &                      _acceptor;
    bool                            _isLooping;
    vector<struct epoll_event>      _evtArr;//存放已经就绪的文件描述符以及事件

    map<int,TcpConnectionPtr>       _conns;//存放已经建立好的连接
    TcpConnectionCallBack           _onConnection;
    TcpConnectionCallBack           _onMessage;
    TcpConnectionCallBack           _onClose;
};
}

#endif

