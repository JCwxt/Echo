#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H
#include "Socket.h"
#include "InetAddress.h"
#include "SocketIo.h"
#include <header.h>

namespace wxt{

class TcpConnection{
public:
    TcpConnection(int fd);
    ~TcpConnection(){}
    void send(const string &);
    string receive();
    void printConnectionInfo() const;
    bool isClosed() const;
private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();


private:
    Socket      _sock;
    InetAddress _addr;
    SocketIO    _sockIO;
    InetAddress _localaddr;
    InetAddress _peeraddr;
};
}

#endif

