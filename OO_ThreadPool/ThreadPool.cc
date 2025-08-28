#include "ThreadPool.h"
#include "WorkThread.h"
#include <unistd.h>
namespace wd{
ThreadPool::ThreadPool(int threadnum,int quesize)
:_threads()
,_taskqueue(quesize)
,_threadnum(threadnum)
,_isExit(false)
{
    _threads.reserve(_threadnum);
}
ThreadPool::~ThreadPool(){
    if(!_isExit){
        stop();
    }
}
void ThreadPool::start(){
    for(int i=0;i<_threadnum;++i){
        unique_ptr<Thread> thread(new WorkThread(*this));
        _threads.push_back(std::move(thread));
    }

    for(auto &th:_threads){
        th->start();
    }
}

void ThreadPool::stop(){
    while(!_taskqueue.empty()){
        sleep(1);
    }

    _isExit=true;
    _taskqueue.wake();

    for(auto &th:_threads){
        th->join();
    }
}
void ThreadPool::addTask(Task *ptask){
    if(ptask){
        _taskqueue.push(ptask);
    }
}

void ThreadPool::doTask(){
    while(!_isExit){
        Task *ptask=_taskqueue.pop();
        if(ptask){
            ptask->process();
        }
    }    
}
}
