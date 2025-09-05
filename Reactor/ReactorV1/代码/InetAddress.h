#ifndef _INETADDRESS_H
#define _INETADDRESS_H

#include <header.h>
#include <string>
using std::string ; 
namespace wxt{
class InetAddress{
public:
    InetAddress(unsigned short port,const string &ip="127.0.0.1");
    explicit InetAddress(const struct sockaddr_in &);
    string ip() const;
    unsigned short port() const;
    struct sockaddr_in *getInetAddress(){ return &_addr; };
private:
    struct sockaddr_in _addr;
};
}
#endif

