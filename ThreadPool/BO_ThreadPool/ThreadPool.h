#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include "Thread.h"
#include "TaskQueue.h"
#include <vector>
#include <memory>
#include <functional>

using std::vector;
using std::unique_ptr;
using std::function;

namespace wd{

using Funtask=function<void ()>;

class ThreadPool{
public:
    ThreadPool(int,int);
    ~ThreadPool();
    void start();
    void stop();
    void addTask(Funtask &&);
    void doTask();
private:
    vector<unique_ptr<Thread>> _threads;
    TaskQueue                  _taskqueue;
    int                        _threadnum;
    bool                       _isExit;
};
}

#endif

