#include "InetAddress.h"

namespace wxt{
InetAddress::InetAddress(unsigned short port,const string &ip)
{
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr(ip.data());
    sockaddr.sin_port=htons(port);
    _addr=sockaddr;
}

InetAddress::InetAddress(struct sockaddr_in addr)
:_addr(addr)
{

}

string InetAddress::ip() const{
    return string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const{
    return ntohs(_addr.sin_port);
}
}
