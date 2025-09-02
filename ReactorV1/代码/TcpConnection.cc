#include "TcpConnection.h"
#include <iostream>
namespace wxt{
TcpConnection::TcpConnection(int fd)
:_sock(fd)
,_addr(fd)
,_sockIO(fd)
,_localaddr(getLocalAddr())
,_peeraddr(getPeerAddr())
{

}

void TcpConnection::send(const string &msg){
    int ret=_sockIO.sendn(msg.data(),msg.length());
    printf("send %d bytes.\n",ret);
}

string TcpConnection::receive(){
    char buff[65535]={0};
    int ret=_sockIO.recvLine(buff,sizeof(buff));
    printf(">>> recv %d bytes ,msg:%s\n",ret,buff);
    return string(buff);
}

bool TcpConnection::isClosed() const{
    char buf[20];
    int ret=_sockIO.recvPeek(buf,sizeof(buf));
    return ret==0;
}

InetAddress TcpConnection::getLocalAddr(){

    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    socklen_t len=sizeof(sockaddr);
    int ret=getsockname(_sock.getFd(),(struct sockaddr *)&sockaddr,&len);
    if(ret<0){
        perror("getsockname");
    }
    return InetAddress(sockaddr);
}

InetAddress TcpConnection::getPeerAddr(){
    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    socklen_t len=sizeof(sockaddr);
    int ret=getpeername(_sock.getFd(),(struct sockaddr*)&sockaddr,&len);
    if(ret<0){
        perror("getpeername");
    }
    return InetAddress(sockaddr);
}

void  TcpConnection::printConnectionInfo() const{
    std::cout<<"tcp:"<<_localaddr.ip()<<":"<<_localaddr.port()
        <<"------>"<<_peeraddr.ip()<<":"<<_peeraddr.port()
        <<"  has connected successful"<<std::endl;
}
}
