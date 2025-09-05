#include "TcpServer.h"

namespace wxt{
TcpServer::TcpServer(unsigned short port,const string &ip)
:_acceptor(port,ip)
,_loop(_acceptor)
{
    _acceptor.Ready();
}

void TcpServer::setAllCallbacks(TcpConnectionCallBack &&cb1,TcpConnectionCallBack &&cb2,TcpConnectionCallBack &&cb3)
{
    _loop.setAllCallbaks(std::move(cb1),std::move(cb2),std::move(cb3));
}

void TcpServer::start(){
    _loop.loop();
}

void TcpServer::stop(){
    _loop.unloop();
}
}
