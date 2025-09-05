#ifndef _THREADPOOL_H
#define _THREAPOOL_H
#include "TaskQueue.h"
#include "Thread.h"
#include <functional>
#include <vector>
#include <memory>

using std::unique_ptr;
using std::vector;
using std::function;
namespace wxt{
   using FuncTask=function<void()>;

class ThreadPool{
public:
    ThreadPool(int,int);
    ~ThreadPool();
    void start();
    void stop();
    void doTask();
    void addTask(FuncTask &&);
private:
    vector<unique_ptr<Thread>> _threads;//工作线程
    int                        _threadNum;//工作线程个数
    TaskQueue                  _que;//任务队列
    bool                       _isExit;//判断线程池是否工作

};
}
#endif

