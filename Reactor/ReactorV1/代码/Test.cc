#include "TcpConnection.h"
#include "Acceptor.h"
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;
void test(){
    wxt::Acceptor acceptor(8080,"127.0.0.1");
    acceptor.Ready();
    
    int netfd=acceptor.accept();

    wxt::TcpConnection conn(netfd);
    if(netfd>0){
        //连接成功
        conn.printConnectionInfo();
    }
    conn.send("weclome to server.");
    conn.receive();

}

int main()
{
 test();
 return 0;
}

