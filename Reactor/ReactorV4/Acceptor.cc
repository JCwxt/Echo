#include "Acceptor.h"

namespace wxt{
Acceptor::Acceptor(unsigned short port,const string &ip)
:_sock()
,_addr(port,ip)
{

}

void Acceptor::Ready(){
    setReuseAddr(true);
    setReusePort(true);
    bind();
    listen();
}

int Acceptor::accept(){
    int netfd=::accept(_sock.getFd(),NULL,NULL);
    if(netfd<0){
        perror("netfd");
    }
    return netfd;
}

void Acceptor::setReuseAddr(bool on){
    int open=1;
    int ret=setsockopt(_sock.getFd(),SOL_SOCKET,SO_REUSEADDR,&open,sizeof(open));
    if(ret<0){
        perror("setsockopt");
    }
}

void Acceptor::setReusePort(bool on){
    int open=1;
    int ret=setsockopt(_sock.getFd(),SOL_SOCKET,SO_REUSEPORT,&open,sizeof(open));
    if(ret<0){
        perror("setsockopt");
    }
}

void Acceptor::bind()
{
    int ret=::bind(_sock.getFd(),(const struct sockaddr*)_addr.getInetAddress(),sizeof(_addr));
    if(ret<0){
        perror("bind");
    }
}

void Acceptor::listen(){
    int ret=::listen(_sock.getFd(),20000);
    if(ret<0){
        perror("bind");
    }
    printf("server is listening.......\n");
}

}

