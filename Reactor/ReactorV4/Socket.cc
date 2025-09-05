#include "Socket.h"
#include <header.h>

namespace wxt{
Socket::Socket()
{
    //创建套接字
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

void Socket::shutDownWrite(){
    //当客户端断开时，关闭客户端到服务器的写端
    int ret=shutdown(_fd,SHUT_WR);
    if(ret<0){
        perror("shutdown");
    }
}
}
