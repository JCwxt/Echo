#ifndef _TCPSERVER_H
#define _TCPSERVER_H
#include "Acceptor.h"
#include "EventLoop.h"

namespace wxt{
class TcpServer{
public:
    TcpServer(unsigned short port,const string &ip);
    void start();
    void stop();
    void setAllCallbacks(TcpConnectionCallBack &&cb1,TcpConnectionCallBack &&cb2,TcpConnectionCallBack &&cb3);

private:
    Acceptor  _acceptor;
    EventLoop _loop;
};
}
#endif

