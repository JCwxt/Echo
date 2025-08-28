#ifndef _WORKTHREAD_H
#define _WORKTHREAD_H

#include "Thread.h"
#include "ThreadPool.h"
namespace wd{
class WorkThread :public Thread{
public:
    WorkThread(ThreadPool &pool)
    :_threadpool(pool)
    {

    }
private:
    void run() override{
        _threadpool.doTask();
    }
private:
    ThreadPool& _threadpool;
};
}
#endif

