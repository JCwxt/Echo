#include "TaskQueue.h"

namespace wd{
TaskQueue::TaskQueue(int size)
:_que()
,_quesize(size)
,_mutex()
,_notEmpty(_mutex)
,_notFull(_mutex)
,_flag(true)
{

}

bool TaskQueue::empty(){
    return 0==_que.size();
}

bool TaskQueue::full(){
    return _que.size()==_quesize;
}

void TaskQueue::push(ElemType e){
    _mutex.lock();

    while(full()){
        _notFull.wait();
    }

    _que.push(e);
    _notEmpty.notifyOne();
    _mutex.unlock();
}

ElemType TaskQueue::pop(){
    _mutex.lock();

    while(empty()&&_flag){
        _notEmpty.wait();
    }
    if(_flag){
        ElemType temp=_que.front();
        _que.pop();
        _notFull.notifyOne();
        _mutex.unlock();
        return temp;
    }else{
        _mutex.unlock();
        return nullptr;
    }
}

void TaskQueue::wake(){
    _notEmpty.notifyAll();
    _flag=false;
}
}
