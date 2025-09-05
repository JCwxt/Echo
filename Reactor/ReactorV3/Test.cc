#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include "TcpServer.h"
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
    wxt::TcpServer server(8080,"0.0.0.0");
    //设置回调函数
    server.setAllCallbacks(onConnection,onMessage,onClose);
    //服务器开始事件循环
    server.start();
}

int main()
{
 test();
 return 0;
}

