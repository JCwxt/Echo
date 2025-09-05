#ifndef _MUTEXLOCK_H
#define _MUTEXLOCK_H

#include "NoCopyable.h"
#include <pthread.h>
namespace wd{

class MutexLock:public wd::NoCopyable{

public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();
    pthread_mutex_t * getMutexLockPtr(){return &_mutex;};
private:
    pthread_mutex_t _mutex;
};
}

#endif

