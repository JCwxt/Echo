#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H
#include "Task.h"
#include "MutexLock.h"
#include "Condition.h"
#include <queue>
namespace wd{

using ElemType=Task *;
class TaskQueue{
public:
    TaskQueue(int);
    bool empty();
    bool full();
    void push(ElemType);
    ElemType pop();
    void wake();
private:
    std::queue<ElemType> _que;
    std::size_t         _quesize;
    MutexLock           _mutex;
    Condition           _notEmpty;
    Condition           _notFull;
    bool                _flag;
};
}
#endif

