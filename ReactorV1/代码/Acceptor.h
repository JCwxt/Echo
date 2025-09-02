#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H
#include "Socket.h"
#include "InetAddress.h"
#include "NoCopyable.h"
namespace wxt{
class Acceptor{

public:
    Acceptor(unsigned short port,const string &ip);
    void Ready();
    int accept();
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

