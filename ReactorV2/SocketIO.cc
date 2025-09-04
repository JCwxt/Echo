#include "SocketIO.h"
#include <header.h>
namespace wxt{
SocketIO::SocketIO(int fd)
:_fd(fd)
{

}

int SocketIO::recvn(char *buf,int len){
    char *pbuf=buf;
    int left=len;
    while(left>0){
        int ret=recv(_fd,buf,left,0);
        if(ret==-1&&errno==EINTR){
            continue;
        }else if(ret==-1){
            perror("recv");
            return len-left;
        }else if(ret==0){
            return len-left;
        }else{
            left-=ret;
            pbuf+=ret;
        }
    }
    return len-left;
}

int SocketIO::sendn(const char *buf,int len){
    const char *pbuf=buf;
    int left=len;
    while(left>0){
        int ret=send(_fd,buf,left,0);
        if(ret==-1&&errno==EINTR){
            continue;
        }else if(ret==-1){
            perror("send");
            return len-left;
        }else if(ret==0){
            return len-left;
        }else{
            left-=ret;
            pbuf+=ret;
        }
    }
    return len-left;
}

int SocketIO::recvPeek(char *buf,int len){
    int ret=-1;
    do{
        ret=recv(_fd,buf,len,MSG_PEEK);
    }while(ret==-1&&errno==EINTR);
    return ret;
}

int SocketIO::recvLine(char *buf,int len){
    int left=len-1;//预留最后一个位置填充'\0'
    char *pbuf=buf;
    int total=0;//统计字符
    while(1){
        //检查是否有无数据
        int ret=recvPeek(pbuf,left);

        //遍历读取到的数据中是否有无'\n'
        for(int i=0;i<ret;++i){
            if(pbuf[i]=='\n'){
                ret=recvn(pbuf,i+1);
                pbuf[i]='\0';
                total+=ret;
                return total;
            }
        }

        //没有找到
        ret=recvn(pbuf,ret);
        left-=ret;
        pbuf+=ret;
        total+=ret;
    }
    //当遍历完还没有找到，则直接返回len-1,即当前缓冲区大小
    pbuf[len-1]='\0';
    return len-1;
}

}
