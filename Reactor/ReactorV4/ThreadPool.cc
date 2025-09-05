#include "ThreadPool.h"
#include <stdio.h>
#include <functional>
#include <unistd.h>
using std::bind;
namespace wxt{
ThreadPool::ThreadPool(int threadnum,int quesize)
:_threads()
,_threadNum(threadnum)
,_que(quesize)
,_isExit(false)
{
    _threads.reserve(_threadNum);
}
ThreadPool::~ThreadPool(){
    if(!_isExit){
        stop();
    }
}
void ThreadPool::start(){
    for(int i=0;i<_threadNum;++i){
        //将工作线程放入vector中管理
        unique_ptr<Thread>  thread(new wxt::Thread(bind(&ThreadPool::doTask,this)));
        _threads.push_back(std::move(thread));
    }
    //启动所有线程
    for(auto &it:_threads){
        it->start();
    }
}
void ThreadPool::stop(){
    while(!_que.empty()){
        sleep(1);//如果任务队列不空，就让其睡眠，等待任务执行
    }

    _isExit=true;
    _que.wake();//唤醒所有等待的线程

    for(auto &it:_threads){
        it->join();//等待子线程执行完毕
    }
}

void ThreadPool::addTask(FuncTask &&task){
    if(task){
        _que.push(std::move(task));
    }
}

void ThreadPool::doTask(){
    //从任务队列取出任务执行
    while(!_isExit){
        FuncTask task=_que.pop();
        if(task){
            task();
        }
    }
}
}
