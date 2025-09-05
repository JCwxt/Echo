#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <iostream>
using std::cout;
using std::endl;
void onConnection(wxt::TcpConnectionPtr conn){
    conn->printfConnectionInfo();
}

void onMessage(wxt::TcpConnectionPtr conn){
    //接收数据
    string msg=conn->receive();
    //回显数据
    conn->send(msg);
}

void onClose(wxt::TcpConnectionPtr conn){
    conn->printfdisConnectionInfo();
}

void test(){
    wxt::Acceptor accptor(8080,"127.0.0.1");
    accptor.Ready();

    wxt::EventLoop loop(accptor);
    loop.setAllCallbaks(onConnection,onMessage,onClose);
    loop.loop();

}

int main()
{
 test();
 return 0;
}

