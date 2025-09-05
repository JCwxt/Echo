#include "ThreadPool.h"
#include <unistd.h>
#include <functional>

using std::bind;
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
        unique_ptr<Thread> thread(new wd::Thread(bind(&ThreadPool::doTask,this)));
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

void ThreadPool::addTask(Funtask &&ptask){
    if(ptask){
        _taskqueue.push(std::move(ptask));
    }
}

void ThreadPool::doTask(){
    while(!_isExit){
        Funtask ptask=_taskqueue.pop();
        if(ptask){
            ptask();
        }
    }    
}
}
