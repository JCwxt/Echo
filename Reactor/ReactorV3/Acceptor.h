#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H
#include "NoCopyable.h"
#include "Socket.h"
#include "InetAddress.h"

namespace wxt{
class Acceptor:NoCopyable{
public:
    Acceptor(unsigned short port,const string &ip);
    ~Acceptor(){}
    void Ready();
    int accept();
    int getFd(){return _sock.getFd();}
private:
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void bind();
    void listen();
private:
    Socket      _sock;
    InetAddress _addr;
};
}
#endif

