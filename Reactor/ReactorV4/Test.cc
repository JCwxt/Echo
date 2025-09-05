#include "TcpConnection.h"
#include "TcpServer.h"
#include "ThreadPool.h"
#include <iostream>
using std::cout;
using std::endl;


wxt::ThreadPool threadpool(4,10);
class MyTask{
public:
    MyTask(const string &msg,wxt::TcpConnectionPtr conn)
    :_msg(msg)
    ,_conn(conn)
    {

    }

    void process(){
        cout<<"compute Thread "<<pthread_self()<<" is process"<<endl;
        //encode
        //compute
        //encode
        string response=_msg;
        /* _conn->send(response); */

        _conn->sendInLoop(response);
    }
private:
    string                _msg;
    wxt::TcpConnectionPtr _conn;
};
void onConnection(wxt::TcpConnectionPtr conn){
    conn->printfConnectionInfo();
}

void onMessage(wxt::TcpConnectionPtr conn){
    //接收数据
    string msg=conn->receive();
    //回显数据
    //将数据封装成一个任务，交给线程池执行
    MyTask task(msg,conn);
    threadpool.addTask(std::bind(&MyTask::process,task));
}

void onClose(wxt::TcpConnectionPtr conn){
    conn->printfdisConnectionInfo();
}

void test(){
    //启动线程池
    threadpool.start();
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

