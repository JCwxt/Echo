#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include "Thread.h"
#include "TaskQueue.h"
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;
namespace wd{
class ThreadPool{

    friend class WorkThread;
public:
    ThreadPool(int,int);
    ~ThreadPool();
    void start();
    void stop();
    void addTask(Task *);
    void doTask();
private:
    vector<unique_ptr<Thread>> _threads;
    TaskQueue                  _taskqueue;
    int                        _threadnum;
    bool                       _isExit;
};
}

#endif

