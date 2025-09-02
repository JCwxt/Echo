#include "Socket.h"
#include <header.h>
namespace  wxt{
Socket::Socket()
:_fd(-1)
{
    _fd=socket(AF_INET,SOCK_STREAM,0);
    if(_fd<0){
        perror("socket");
    }
}

Socket::Socket(int fd)
:_fd(fd)
{

}

Socket::~Socket(){
    if(_fd>0){
        close(_fd);
    }
}

}
