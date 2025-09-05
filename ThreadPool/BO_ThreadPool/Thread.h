#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>
#include <functional>

using std::function;

namespace wd{
using ThreadCallback=function<void() >;
class Thread {
public:
    Thread( ThreadCallback && );
    virtual ~Thread(){}
    void start();
    void join();
private:
    static  void * start_routine(void *);
private:
    ThreadCallback _cb;
    pthread_t _pthid;
    bool _isrunning;
};
}
#endif

