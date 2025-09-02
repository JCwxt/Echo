#include "SocketIo.h"
#include <header.h>
#include <errno.h>
namespace wxt{
SocketIO::SocketIO(int fd)
:_fd(fd)
{

}

int SocketIO::recvn(char * buf,int len){
    int left=len;
    char *pbuf=buf;
    while(left>0){
        int ret=recv(_fd,pbuf,left,0);
        if(ret==-1&&errno==EINTR){
            continue;
        }else if(ret==-1){
            perror("recv");
            return len-left;
        }else if(ret==0){
            /* close(_fd); */
            return len-left;
        }else{
            left-=ret;
            pbuf+=ret;
        }
    }
    return len-left;
}

int SocketIO::sendn( const char *buf,int len){
    int left=len;
    const char *pbuf=buf;
    while(left>0){
        int ret=send(_fd,pbuf,left,0);
        if(ret==-1&&errno==EINTR){
            return len-left;
        }
        else if(ret==-1){
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

//检查缓冲区中是否有数据
int SocketIO::recvPeek(char * buf,int len) const{
    int ret=-1;
    do{
        ret=recv(_fd,buf,len,MSG_PEEK);//只查看数据，不移走数据
    }while(ret==-1&&errno==EINTR);
    return ret;
}

int SocketIO::recvLine(char * buf,int len){

    int left=len-1;//预留缓冲区的最后一个位置'\0';
    char *pbuf=buf;
    int total=0;//统计字符个数
    while(left>0){
        //先找到数据的第一个'\n'的位置
        //查看内核数据缓冲区中的数据，但是不移走
        int ret=recvPeek(pbuf,left);

        //遍历刚刚读取的数据中是否有'\n'
        for(int i=0;i<ret;++i){
            if(pbuf[i]=='\n'){
                //找到了'\n'
                //将'\n'之前的数据读出
                ret=recvn(pbuf,i+1);
                total+=ret;
                pbuf[i]='\0';//将'\n'换成'\0'
                return total;
            }
        }

        //没有找到
        ret=recvn(pbuf,ret);
        left-=ret;
        pbuf+=ret;
        total+=ret;
    }

    //如果缓冲区满了，此时还没找到'\n',则将缓冲区的最后一个位置设为'\n'，返回
    pbuf[len-1]='\0';
    return len-1;
}
}
