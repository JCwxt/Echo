#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>
#include "NoCopyable.h"
namespace wd{

class Thread :public NoCopyable{
public:
    Thread();
    virtual ~Thread(){}
    void start();
    void join();
private:
    static  void * start_routine(void *);
    virtual void run()=0;
private:
    pthread_t _pthid;
    bool _isrunning;
};
}
#endif

