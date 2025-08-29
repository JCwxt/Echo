### Qt网络编程

#### 1.socket网络编程函数

服务器：int listenfdsocket，bind ，listen,int connfd=accept,read/recv/write/send,close

客户端：int fd=socket,connect,read/recv/write/send,close

#### 2.TCP网络编程

##### 2.1 TCP协议

用于数据传输的低级网络协议，它是可靠的，面向连接的，面向流的传输协议，适合用于连续数据的传输。

##### 2.2 通信原理

  