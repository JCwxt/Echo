#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H

#include "InetAddress.h"
#include "SocketIO.h"
#include "Socket.h"
#include "NoCopyable.h"
#include <functional>
#include <memory>

using std::function;
using std::shared_ptr;

namespace  wxt{
class EventLoop;
class TcpConnection;
using TcpConnectionPtr=shared_ptr<TcpConnection>;
using TcpConnectionCallBack=function<void (TcpConnectionPtr)>;

class TcpConnection:NoCopyable,public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd,EventLoop *loop);
    void sendInLoop(const string &msg);//线程池使用TcpConnection的对象发送数据给EventLoop
    string receive();
    void send(const string&);
    bool isClosed();
    
    void printfConnectionInfo();
    void printfdisConnectionInfo();
   
    void setAllCallbacks( const TcpConnectionCallBack &cb1,const TcpConnectionCallBack &cb2,const TcpConnectionCallBack &cb3);
    void handleNecConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();


private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
private:
    SocketIO                 _sockIO;
    Socket                   _sock;
    InetAddress              _localAddr;
    InetAddress              _peerAddr;
    
    TcpConnectionCallBack    _onConnection;
    TcpConnectionCallBack    _onMessage;
    TcpConnectionCallBack    _onClose;
   
    EventLoop*               _loop;
};
}
#endif

