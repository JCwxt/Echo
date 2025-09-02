#ifndef _SOCKET_H
#define _SOCKET_H
namespace wxt{
class Socket{
public:
    Socket();
    explicit Socket(int fd);
    ~Socket();
    int getFd(){return _fd;}
    void shutdownWrite();
private:
    int _fd;
};
}

#endif//!_SOCKET_H

