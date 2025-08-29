### Linux 网络编程

**常用协议的端口号：**

HTTP(S)   80/443

SSH           22

FTP           21/20

DNS          53

MySQL      3306

Redis         6379

TCP的序号和确认号解决了可靠传输问题。

序号的值会采取随机算法得到一个随机值。

确认号：告诉对端确认号之前的数据都已经收到了，接下来要开始从确认号之后的数据开始发送。

当ACK（确认位）标志为1时，确认号才有效。

最大传输单元：MTU=1500

TCP报文的长度最大值MSS =MTU-IP头（20）-TCP(头)=1460

![image-20250829104840432](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250829104840432.png)

**TCP协议的特点**

TCP协议是一个传输层的协议

TCP是面向连接的协议。面向连接的含义通信的双方彼此之间维护了一张状态图。

> [!IMPORTANT]
>
> **Question:状态在代码中怎么实现**
>
> enum  Status{
>
> ​           CLOSED,
>
> ​            LISTEN,
>
> ​             ...........
>
> }

TCP是可靠的协议。

TCP是一个二进制协议。

TCP是一个全双工的协议。



建立连接时有五个状态 Closed

断开连接时有6个状态。



为什么叫一个TCP连接

五元组信息一旦确定，那么就会被操作系统认为是同一个连接。



![image-20250829150644869](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250829150644869.png)



```c++
int listen(int sockfd,int backlog);
//sockfd:socket的返回值
//backlog：指令同时能处理的最大连接数要求，通常为10或者5，最大可设为128.
```

backlog的值设置了服务器能同时处理的连接数，通过测试分析服务器能够处理的连接数是backlog+1。

![image-20250829152134625](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250829152134625.png)

客户端的网络地址由操作系统自动分配。

connect绑定的是服务器的ip和端口。