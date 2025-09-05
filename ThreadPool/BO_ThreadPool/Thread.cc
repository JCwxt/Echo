#include "Thread.h"
#include <string.h>
#include <stdio.h>
namespace wd{

Thread::Thread(ThreadCallback &&cb)
:_cb(std::move(cb))
,_pthid(0)
,_isrunning(false)
{

}

void Thread::start(){
    if(!_isrunning){
        int ret=pthread_create(&_pthid,NULL,start_routine,this);
        if(ret!=0){
            fprintf(stderr,"%s\n",strerror(ret));
        }
    }
    _isrunning=true;
}

void Thread::join(){
    if(_isrunning){
        pthread_join(_pthid,NULL);
        _isrunning=false;
    }
}

void * Thread::start_routine(void *arg){
    Thread* pth=static_cast<Thread *>(arg);

    if(pth){
        pth->_cb();
    }
    return NULL;
}
}
