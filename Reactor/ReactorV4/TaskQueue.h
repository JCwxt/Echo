#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H
#include "MutexLock.h"
#include "Condition.h"
#include <functional>
#include <queue>
using std::function;
using std::queue;

namespace wxt{

using ElemType=function<void()>;

class TaskQueue{
public:
    TaskQueue(size_t);
    bool empty();
    bool full();
    void wake();
    ElemType pop();
    void push(ElemType &&);

private:
    queue<ElemType>    _que;
    size_t                _queSize;
    MutexLock          _mutex;
    Condition          _notEmpty;
    Condition          _notFull;
    bool               _flag;
};

}
#endif

