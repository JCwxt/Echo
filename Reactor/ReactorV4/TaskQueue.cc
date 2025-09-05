#include "TaskQueue.h"

namespace wxt{

TaskQueue::TaskQueue(size_t quesize)
:_que()
,_queSize(quesize)
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
   return _queSize==_que.size(); 
}

ElemType TaskQueue::pop(){
    //先加锁
    _mutex.lock();
    while(empty()&&_flag){
        _notEmpty.wait();//等待不空条件唤醒
    }
    if(_flag){
    ElemType temp=_que.front();
    _que.pop();
    _notFull.notifyOne();//唤醒不满条件
    _mutex.unlock();
    return temp;
    }else{
        _mutex.unlock();
        return nullptr;
    }
}

void TaskQueue::push(ElemType &&task){
    _mutex.lock();
    while(full()){
        _notFull.wait();//等待不满条件唤醒
    }
    
    _que.push(std::move(task));//将任务加入任务队列
    _notEmpty.notifyOne();//唤醒不空条件
    _mutex.unlock();
}

void TaskQueue::wake(){
    //唤醒所有在不空条件上等待的线程
    _notEmpty.notifyAll();
    _flag=false;
}
}
