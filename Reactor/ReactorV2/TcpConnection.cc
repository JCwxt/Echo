#include "TcpConnection.h"
#include <iostream>
namespace wxt{

TcpConnection::TcpConnection(int fd)
:_addr(fd,"")
,_sockIO(fd)
,_sock(fd)
,_localAddr(getLocalAddr())
,_peerAddr(getPeerAddr())
{

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
    int ret=getpeername(_sock.getFd(),(struct sockaddr *)&sockaddr,&len);
    if(ret<0){
        perror("getsockname");
    }
    return InetAddress(sockaddr);
}

string TcpConnection::receive(){
    char buf[65535]={0};
    int ret=_sockIO.recvLine(buf,sizeof(buf));
    printf(">>> recv %d bytes,msg:%s.\n",ret,buf);
    return string(buf);
}
void TcpConnection::send(const string &msg){
    int ret=_sockIO.sendn(msg.data(),msg.size());
    printf("<<< send %d bytes.\n",ret);
}

bool TcpConnection::isClosed(){
    char buf[20];
    int ret=_sockIO.recvPeek(buf,sizeof(buf));
    return ret==0;
}

void TcpConnection::printfConnectionInfo(){
    std::cout<<_localAddr.ip()<<":"<<_localAddr.port()<<"------------>"
             <<_peerAddr.ip()<<":"<<_peerAddr.port()
             <<" has connected successful!"<<std::endl;
}

void TcpConnection::printfdisConnectionInfo(){
    if(isClosed()){
        std::cout<<_localAddr.ip()<<":"<<_localAddr.port()<<"------------>"
             <<_peerAddr.ip()<<":"<<_peerAddr.port()
             <<" has closed!"<<std::endl;
    }
}

void TcpConnection:: setAllCallbacks(const TcpConnectionCallBack &cb1,const TcpConnectionCallBack &cb2,const TcpConnectionCallBack &cb3){
    _onConnection=cb1;
    _onMessage=cb2;
    _onClose=cb3;
}
void TcpConnection::handleNecConnectionCallback(){
    if(_onConnection){
        _onConnection(shared_from_this());
    }
}
void TcpConnection:: handleMessageCallback(){
    if(_onMessage){
        _onMessage(shared_from_this());
    }
}
void TcpConnection::handleCloseCallback(){
    if(_onClose){
        _onClose(shared_from_this());
    }
}
}
