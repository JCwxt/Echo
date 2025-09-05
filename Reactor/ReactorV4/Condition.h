#ifndef _CONDITION_H
#define _CONDITION_H

#include "NoCopyable.h"
#include <pthread.h>
namespace wxt{
class MutexLock;
class Condition: NoCopyable{
public:
    Condition(MutexLock &);
    ~Condition();
    void wait();
    void notifyOne();
    void notifyAll();
private:
    pthread_cond_t _cond;
    MutexLock &mutex;
};
}
#endif

