#ifndef _SOCKET_H
#define _SOCKET_H
#include "NoCopyable.h"

namespace wxt{
class Socket:NoCopyable{
public:
    Socket();
    explicit Socket(int fd);
    ~Socket();
    int getFd(){ return _fd; }
    void shutDownWrite();
private:
    int _fd;

};
}
#endif

