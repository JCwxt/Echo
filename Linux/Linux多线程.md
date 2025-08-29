## Linux多线程

**Question1：一个程序的内存布局是怎么样的？**

比如：32位系统，每一个进程都有自己的虚拟地址空间（4G）。

用户态(0G~3G)：

栈区，堆区，全局静态区，文字常量区，程序代码区(函数的二进制表示)。

内核态（3G~4G）

**Question2:malloc的底层实现？**

#### 1.为什么要有多线程？

要充分利用进程的资源，做到并行。

并发：在同一时间段内，有多个任务在执行

并行：在同一时刻内，有多个任务在执行。

单核：只有并发，没有并行

多核：100%并行。

一核代表的是一个cpu计算单元，那么多线程最好做到100%并行。

> [!TIP]
>
> **Question:线程池中有几个线程？（高频）**
>
> 取决于CPU的核数，1核最好对应1~2个线程。
>
> 

#### 2.线程间关系

所有线程共享同一进程的资源(虚拟地址空间)，子线程之间可以相互等待，但是子线程不能等待主线程。

main线程是进程的入口，当main线程退出时，子线程也结束了。

所有子线程在进程内部都是平等的。

子线程内部依然可以创建子线程。

> [!TIP]
>
> **Question：每个子线程区别于其它线程的地方？**
>
> TCB---->PCB----->Linux中的PCB叫struct task_struct
>
> 每一个子线程都有自己的函数栈空间（单独控制）。

#### 3.POSIX线程库

头文件

```c++
#include <pthread.h>
```

##### 1.线程的创建

```c++
int pthread_create(pthread_t *thread,const phtread_arr_t *attr,void *(*start_routine)(void *),void *arg);
```

**pthread_t *thread** **:**传递一个指针，该函数执行结束后，会修改线程ID。

**const phtread_arr_t *attr：**线程属性，一般情况下，直接设置为NULL。

**void *(*start_routine)(void *)：**函数指针，代表的是线程的入口函数。

**void *arg：**arg给线程入口函数传递参数。

<font color='red'>**void *** </font>可以看作所有类型的基类，可以向下转换成任意类型。

> [!TIP] 
>
> cout是c++中的标准输出流对象,<<输出流运算符重载，是一个函数。endl一个内联函数。
>
> printf是C的标准库函数
>
> 在执行打印时，printf的效率高于cout。

获取错误信息

```c++
#include <string.h>
strerror(int errornum);
```

子线程要得到执行，必须要在main函数退出之前，main函数退出，整个进程就会退出。

在Linux，从内核的角度来看，只有进程没有线程概念，线程叫做LWP轻量级进程**struct task_struct,**俗称的进程控制块PCB。

通过<font color='red'>**ps -elLf**</font>可以查看子线程情况。

**ps -elf**只能查看进程状态，无法查看线程情况。

**获取当前线程的id <font color='red'>pthread_self</font>。**

##### 2.线程的等待

主线程要等待子线程执行完毕再退出。

```C++
int pthread_join(pthread_t thread,void **retval);
```

##### 3.线程的退出

pthread_exit(NULL);

退出子线程。更推荐使用**return NULL**

##### 4.线程的实现

```C++
//头文件
#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>

namespace Thread{

class Thread{
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

//实现文件
#include "Thread.h"
#include <string.h>
#include <stdio.h>
namespace Thread{
    Thread::Thread()
    :_pthid(0),_isrunning(false)
    {}

    void Thread::start(){
        if(!_isrunning){
            int ret=pthread_create(&_pthid,NULL,start_routine,this);
            if(ret!=0){
                fprintf(stderr,"%s\n",strerror(ret));
            }
        }
        _isrunning=true;
    }
    void Thread::join(){
        if(_isrunning){
            pthread_join(_pthid,NULL);
            _isrunning=false;
        }
    }

    void *Thread::start_routine(void *arg){
        Thread* thread=static_cast<Thread *> (arg);
        if(thread){
            thread->run();
        }
        return NULL;
    }


}

//测试文件
#include <iostream>
#include "Thread.h"
#include <time.h>
#include <memory>
#include <unistd.h>
using namespace std;
class MyThread:public Thread::Thread
{
public:
    void run() override{
        srand(time(NULL));
        for(int i=0;i<10;++i){
            int num=rand()%100+1;
            printf("create num:%d\n",num);
            sleep(1);
        }
    }
   ~MyThread() override{}

};
void test(){
    unique_ptr<Thread::Thread> thread(new MyThread);
    thread->start();
    thread->join();
}

int main()
{
 test();
 return 0;
}
```

> [!TIP]
>
> **Qusetion:线程可以复制吗？**
>
> 线程是系统资源，在语义上不能进行复制，所以拷贝构造函数和赋值运算符函数都不能直接调用。应该表达对象语义，不能复制和赋值。

可以在基类中将拷贝构造函数和赋值运算符函数删除，那么派生类就无法使用拷贝构造函数和赋值运算符函数了，因为派生类在调用拷贝构造和赋值运算符函数时会先调用基类的拷贝构造和赋值运算符函数来完成对基类部分的拷贝和赋值。

```C++
Mythread t1;
Mythread t2=t1//error
Mythread t3;
t3=t1;//error
```

#### 3.互斥锁

**互斥锁类型：**pthread_mutex_t  t代表type

**互斥锁的属性：**一般情况直接设置为NULL.

<font color='red'>**互斥锁不能复制和赋值，互斥锁也是系统资源。**</font>

**初始化方式：**

- 静态初始化：PTHREAD_MUTEX_INITALIZER.
- 动态初始化：通过调用pthread_mutex_init，推荐使用。

**加锁：**pthread_mutex_lock,pthread_mutext_trylock.

**解锁：**pthread_mutex_unlock

某一个线程加锁后，必须要该线程解锁。加锁解锁必须成对出现。

**销毁锁：**pthread_mutex_destory.

> [!NOTE]
>
> **Question:同一个线程可以加多次互斥锁吗？**
>
> 如果是第一次，会加锁成功，加锁之后会返回。
>
> 如果再加一次锁，此时会阻塞。
>
> 如果有一个线程A加锁成功了，但是还没有解锁，此时B也想加锁，线程B会被阻塞

```c++
#include <pthread.h>
#include <stdio.h>
using namespace std;
int gnumber=0;
pthread_mutex_t mutex;
void * start_routine1(void *){

    int cnt=1000000;
    while(cnt--){
        pthread_mutex_lock(&mutex);
        gnumber++;
        pthread_mutex_unlock(&mutex);
        printf("sub thread 1 is running\n");
    }
    return NULL;
}
void * start_routine2(void *){

    int cnt=1000000;
    while(cnt--){
        pthread_mutex_lock(&mutex);
        gnumber++;
        pthread_mutex_unlock(&mutex);
        printf("sub thread 2 is running\n");
    }
    return NULL;
}
    
void test(){
    //初始化锁
    pthread_mutex_init(&mutex,NULL);

    pthread_t pthid1=0;
    pthread_t pthid2=0;
    
    pthread_create(&pthid1,NULL,start_routine1,NULL);
    pthread_create(&pthid2,NULL,start_routine2,NULL);
    
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);

    printf("gnumber=%d\n",gnumber);
    //2.销毁锁
    pthread_mutex_destroy(&mutex);
}

int main()
{
 test();
 return 0;
}
```

#### 4.条件变量

**pthread_cond_t**

**条件变量的等待**

```c++
int pthread_cond_wait(pthread_cond_t * cond,pthread_mutex_t * mutex);
```

**上半部分：**当线程A调用wait函数时，线程A会进入阻塞状态，但在阻塞之前会先解锁。

**下半部分：**当线程A被唤醒之后，首先要进行加锁，加锁成功之后，才返回，如果加锁没有成功，则继续阻塞，直到加锁成功。

**唤醒线程**

```c++
//唤醒一个线程
int pthread_cond_signal(pthread_cond_t *cond);

//唤醒所有线程
int pthread_cond_broadcast(pthread_cond_t *cond);
```

**线程的同步实现**

```c++
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

int flag=0;//flag=1 线程1执行，否则线程2执行
pthread_mutex_t mutex;
pthread_cond_t cond;
int gnumber=0;
void * start_routine(void *){
    printf("sub thread 1 is running\n");
    int cnt=100000;
    while(cnt--){
        pthread_mutex_lock(&mutex);
        while(flag==0){
            pthread_cond_wait(&cond,&mutex);
        }
        flag=0;
        gnumber++;
        pthread_cond_signal(&cond);//唤醒2号线程
        printf("sub thread 1 gnumber is %d\n",gnumber);
        pthread_mutex_unlock(&mutex);

    }
    return NULL;
}
void * start_routine2(void *){

    printf("sub thread 2 is running\n");
    int cnt=100000;
    while(cnt--){
        pthread_mutex_lock(&mutex);
        while(flag==1){
            pthread_cond_wait(&cond,&mutex);
        }
        flag=1;
        gnumber++;
        pthread_cond_signal(&cond);//唤醒1号线程
        printf("sub thread 2 gnumber is %d\n",gnumber);
        pthread_mutex_unlock(&mutex);

    }
    return NULL;
}
void test(){
    //1.初始化互斥锁
    pthread_mutex_init(&mutex,NULL);
    //2.初始化条件变量
    pthread_cond_init(&cond,NULL);

    //3.创建线程
    pthread_t pth_id1,pth_id2;

    pthread_create(&pth_id1,NULL,start_routine,NULL);
    pthread_create(&pth_id2,NULL,start_routine2,NULL);

    pthread_join(pth_id1,NULL);
    pthread_join(pth_id2,NULL);
    
    //4.销毁互斥锁
    pthread_mutex_destroy(&mutex);
    //5.销毁条件变量
    pthread_cond_destroy(&cond);

    printf("main gnumber is %d\n",gnumber);
}

int main()
{
 test();
 return 0;
}
```

#### 5.互斥锁和条件变量的封装

引用依然占据一个指针大小的空间。

**#include <xxx.h>头文件**是从系统路径之下开始查找。

**#include "xxx.h”头文件**表示自定义头文件，从当前路径之下查找。 

> [!CAUTION]
>
> **<font color='red'>Question：NULL和nullptr的区别？</font>**
>
> **1.类型不同**：
>
> - `NULL`通常是宏定义，在 C++ 中被定义为`0`（整数零）
>
> - `nullptr`是 C++11 引入的关键字，是一种特殊的空指针常量，类型为`nullptr_t`。
>
> **2.模板推导时的差异**：
>
> - 使用`NULL`可能导致模板推导出`int`类型
> - `nullptr`能正确推导出指针类型
>
> **3.安全性**：
>
> - `nullptr`在处理空指针时更安全，避免了将`0`误用作指针的歧义
> - 对于重载了整数和指针版本的函数，`nullptr`能明确选择指针版本

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250826204656713.png" alt="image-20250826204656713" style="zoom:67%;" />

```c++
//互斥锁的头文件
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

//互斥锁的实现文件
#include "MutexLock.h"

namespace wd{
MutexLock::MutexLock(){
    //初始化互斥锁
    pthread_mutex_init(&_mutex,NULL);
}
MutexLock::~MutexLock(){
    //销毁互斥锁
    pthread_mutex_destroy(&_mutex);
}
void MutexLock::lock(){
    pthread_mutex_lock(&_mutex);
}
void MutexLock::unlock(){
    pthread_mutex_unlock(&_mutex);
}
}

//条件变量的头文件
#ifndef _CONDITION_H
#define _CONDITION_H

#include "NoCopyable.h"
#include <pthread.h>
namespace wd{
class MutexLock;
class Condition:public wd::NoCopyable{
public:
    Condition(MutexLock &);
    ~Condition();
    void wait();
    void noitfone();
    void noitfyAll();
private:
    pthread_cond_t _cond;
    MutexLock &mutex;
};
}
#endif

//条件变量的实现文件
#include "Condition.h"
#include "MutexLock.h"
namespace wd{
Condition::Condition(MutexLock &rhs)
:mutex(rhs)
{
    pthread_cond_init(&_cond,NULL);

}
Condition::~Condition(){
    pthread_cond_destroy(&_cond);
}
void Condition::wait(){
    pthread_cond_wait(&_cond,mutex.getMutexLockPtr());
}
void ::noitfyone(){
    pthread_cond_signal(&_cond);
}
void Condition::noitfyAll(){
    pthread_cond_broadcast(&_cond);
}
}
```

#### 6.生产者消费者

##### 类图

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250827143633656.png" alt="image-20250827143633656" style="zoom:67%;" />

##### **代码实现**

```C++
//Thread.h
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
```

```C++
//Thread.cc
#include "Thread.h"
#include <string.h>
#include <stdio.h>
namespace wd{
    Thread::Thread()
    :_pthid(0),_isrunning(false)
    {}

    void Thread::start(){
        if(!_isrunning){
            int ret=pthread_create(&_pthid,NULL,start_routine,this);
            if(ret!=0){
                fprintf(stderr,"%s\n",strerror(ret));
            }
        }
        _isrunning=true;
    }
    void Thread::join(){
        if(_isrunning){
            pthread_join(_pthid,NULL);
            _isrunning=false;
        }
    }

    void *Thread::start_routine(void *arg){
        Thread* thread=static_cast<Thread *> (arg);
        if(thread){
            thread->run();
        }
        return NULL;
    }


}
```

```C++
//MutexLock.h
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
```

```c++
//MutexLock.cc
#include "MutexLock.h"

namespace wd{
MutexLock::MutexLock(){
    //初始化互斥锁
    pthread_mutex_init(&_mutex,NULL);
}
MutexLock::~MutexLock(){
    //销毁互斥锁
    pthread_mutex_destroy(&_mutex);
}
void MutexLock::lock(){
    pthread_mutex_lock(&_mutex);
}
void MutexLock::unlock(){
    pthread_mutex_unlock(&_mutex);
}
}
```

```c++
//Condition.h
#ifndef _CONDITION_H
#define _CONDITION_H

#include "NoCopyable.h"
#include <pthread.h>
namespace wd{
class MutexLock;
class Condition:public wd::NoCopyable{
public:
    Condition(MutexLock &);
    ~Condition();
    void wait();
    void noitfone();
    void noitfyAll();
private:
    pthread_cond_t _cond;
    MutexLock &mutex;
};
}
#endif
```

```c++
//Condition.cc
#include "Condition.h"
#include "MutexLock.h"
namespace wd{
Condition::Condition(MutexLock &rhs)
:mutex(rhs)
{
    pthread_cond_init(&_cond,NULL);

}
Condition::~Condition(){
    pthread_cond_destroy(&_cond);
}
void Condition::wait(){
    pthread_cond_wait(&_cond,mutex.getMutexLockPtr());
}
void Condition::noitfone(){
    pthread_cond_signal(&_cond);
}
void Condition::noitfyAll(){
    pthread_cond_broadcast(&_cond);
}
}
```

```c++
//TaskQueue.h
#ifndef _TaskQueue_H
#define _TaskQueue_H

#include "MutexLock.h"
#include "Condition.h"
#include <queue>

using std::queue;
namespace wd{
    class TaskQueue{
       public:
           TaskQueue (int);
           ~TaskQueue(){}
           bool empty();
           bool full();
           void push(int);
           int pop();
       private:
           queue<int> _que;
           size_t     _quesize;
           MutexLock  _mutex;
           Condition  _notEmpty;
           Condition  _notFull;
    };
}
#endif
```

```c++
//TaskQueue.cc
#include "TaskQueue.h"

namespace wd{
   TaskQueue::TaskQueue(int size)
   :_que()
   ,_quesize(size)
   ,_mutex()
   ,_notEmpty(_mutex)
   ,_notFull(_mutex)
   {
   }

   bool  TaskQueue::empty(){
       return _que.size()==0;
   }

   bool TaskQueue::full(){
       return _que.size()==_quesize;
   }

   void TaskQueue::push(int elem){
       _mutex.lock();
       while(full()){
           _notFull.wait();//等待不满才能添加数据
       }
       _que.push(elem);
       _notEmpty.noitfone();//唤醒在不空条件变量上等待的线程
       _mutex.unlock();
   }

   int TaskQueue::pop(){
       _mutex.lock();
       while(empty()){
           _notEmpty.wait();//等待不空才能消费数据
       }
       int temp=_que.front();
       _que.pop();
       _notFull.noitfone();//唤醒在不满条件变量上等待的线程
       _mutex.unlock();
       return temp;
   }
}
```

```c++
//ProduceThread.h
#ifndef _ProduceThread_H
#define _ProduceThread_H
#include "Thread.h"
#include "TaskQueue.h"
namespace wd{
     class ProduceThread:public Thread{
          public:
              ProduceThread(TaskQueue &);
          private:
              void run() override;
          private:
              wd::TaskQueue &_taskQue;
     };
}
#endif
```

```c++
//ProduceThread.cc
#include "ProduceThread.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
namespace wd{
ProduceThread::ProduceThread(TaskQueue &task)
:_taskQue(task)
{

}

void ProduceThread::run(){
    srand(time(nullptr));
    int cnt=10;
    while(cnt--){
        int num=rand()%100;
        printf("Produce make a number is %d\n",num);
        _taskQue.push(num);
        sleep(1);
    }
}
}
```

```c++
//ConsumerThread.h
#ifndef _CONSUMERTHREAD_H
#define _CONSUMERTHREAD_H

#include "Thread.h"
#include "TaskQueue.h"
namespace wd{
    class ConsumerThread:public Thread{
        public:
            ConsumerThread(TaskQueue &);
        private:
            void run() override;
        private:
            TaskQueue &_taskque;
     };
}
#endif
```

```c++
//ConsumerThread.cc
#include "ConsumerThread.h"
#include <stdio.h>
namespace  wd{
  ConsumerThread::ConsumerThread(TaskQueue &task)
  :_taskque(task)
  {

  }
  void ConsumerThread::run(){
      int cnt=10;
      while(cnt--){
          int num=_taskque.pop();
          printf("Consumer get a number is %d\n",num);
      }
  }
}
```

```c++
//测试文件
#include <iostream>
#include "TaskQueue.h"
#include "ProduceThread.h"
#include "ConsumerThread.h"
#include <memory>
using namespace std;
void test(){
    wd::TaskQueue taskqueue(10);
    unique_ptr<wd::Thread> produce(new wd::ProduceThread(taskqueue));
    unique_ptr<wd::Thread> consumer(new wd::ConsumerThread(taskqueue));

    produce->start();
    consumer->start();

    produce->join();
    consumer->join();
}

int main()
{
 test();
 return 0;
}
```

#### 7.线程池

C10K 10000个连接

RAII 资源获取即初始化

Resource Acquisition is Initialization

，+ u 跳转到函数的实现文件

##### 类图

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250827172200006.png" alt="image-20250827172200006" style="zoom: 50%;" />

##### 代码实现

```c++
// ThreadPool.h
#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include "TaskQueue.h"
#include "Thread.h"
#include "Task.h"
#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr;
namespace  wd{

class ThreadPool{

    friend class WorkThread;
       public:
           ThreadPool(int,int);
           ~ThreadPool();
           void start();
           void stop();
           void doTask();
           void addTask(Task *);
       private:
           vector<unique_ptr<Thread>>  _threads;
           int                         _threadNum;
           TaskQueue                   _taskque;
           bool                        _isExit;
    };
}
#endif
```

```C++
//ThreadPool.cc
#include "ThreadPool.h"
#include "WorkThread.h"
#include <unistd.h>
namespace wd{
ThreadPool::ThreadPool(int threadnum,int quesize)
:_threads()
,_threadNum(threadnum)
,_taskque(quesize)
,_isExit(false)
{
    _threads.reserve(_threadNum);

}
ThreadPool::~ThreadPool(){
    if(!_isExit){
        stop();
    }
}
void ThreadPool::start(){
    
    //1.将所有线程加入任务队列
    for(int i=0;i<_threadNum;++i){
        unique_ptr<Thread> up(new WorkThread(*this));
        _threads.push_back(std::move(up));
    }

    //2.遍历所有的线程并启动
    for(auto &pth:_threads){
        pth->start();
    }
}
void ThreadPool::stop(){
    //只要任务队列不为空就继续执行
    while(!_taskque.empty()){
        sleep(1);
    }

    //任务队列为空，修改标志位，准备退出线程池
    _isExit=true;
    _taskque.weak();
    //让主线程等待子线程执行完毕
    for(auto &pth :_threads){
        pth->join();
    }
}

void ThreadPool::addTask(Task *task)
{
    if(task){
        _taskque.push(task);
    }
}

void ThreadPool::doTask(){
    while(!_isExit){
        Task *ptask=_taskque.pop();
        if(ptask){
            ptask->process();
        }
    }
}

}
```

```C++
//TaskQueue.h
#ifndef _TaskQueue_H
#define _TaskQueue_H

#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"
#include <queue>
using std::queue;
namespace wd{
    using ElemType= Task *;
    class TaskQueue{
       public:
           TaskQueue (int);
           ~TaskQueue(){}
           bool empty();
           bool full();
           void push(ElemType);
           ElemType pop();
           void weak();
       private:
           queue<ElemType> _que;
           size_t     _quesize;
           MutexLock  _mutex;
           Condition  _notEmpty;
           Condition  _notFull;
           bool       _flag;
    };
}
#endif
```

```c++
//TaskQueue.cc
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

   bool  TaskQueue::empty(){
       return _que.size()==0;
   }

   bool TaskQueue::full(){
       return _que.size()==_quesize;
   }

   void TaskQueue::push(ElemType elem){
       _mutex.lock();
       while(full()){
           _notFull.wait();//等待不满才能添加数据
       }
       _que.push(elem);
       _notEmpty.notifyOne();//唤醒在不空条件变量上等待的线程
       _mutex.unlock();
   }

   ElemType TaskQueue::pop(){
       _mutex.lock();
       while(empty()){
           _notEmpty.wait();//等待不空才能消费数据
       }
       if(_flag){
           ElemType temp=_que.front();
           _que.pop();
           _notFull.notifyOne();//唤醒在不满条件变量上等待的线程
          _mutex.unlock();
          return temp;
       }else{
           _mutex.unlock();
           return nullptr;
       }
   }
   void TaskQueue::weak(){
       _flag=false;
      _notEmpty.notifyAll(); 
   }
}
```

```c++
//Thread.h
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
```

```c++
//Thread.cc
#include "Thread.h"
#include <string.h>
#include <stdio.h>
namespace wd{
    Thread::Thread()
    :_pthid(0),_isrunning(false)
    {}

    void Thread::start(){
        if(!_isrunning){
            int ret=pthread_create(&_pthid,NULL,start_routine,this);
            if(ret!=0){
                fprintf(stderr,"%s\n",strerror(ret));
            }
        }
        _isrunning=true;
    }
    void Thread::join(){
        if(_isrunning){
            pthread_join(_pthid,NULL);
            _isrunning=false;
        }
    }

    void *Thread::start_routine(void *arg){
        Thread* thread=static_cast<Thread *> (arg);
        if(thread){
            thread->run();
        }
        return NULL;
    }
}
```

```c++
//WorkThread.h
#ifndef _WORKTHREAD_H
#define _WORKTHREAD_H

#include "Thread.h"
#include "ThreadPool.h"
namespace wd{

class WorkThread:public Thread{
public:
    WorkThread(ThreadPool &t)
    :_threadpool(t)
    {

    }
private:
    ThreadPool& _threadpool;
private:
    void run() override{
        _threadpool.doTask();
    }
};
}

#endif
```

```c++
//Task.h
#ifndef  _TASK_H
#define  _TASK_H

namespace wd{

class Task{
public:
    virtual void process()=0;
};
}
#endif
```

```c++
//TestThreadPool.cc
#include "Task.h"
#include "ThreadPool.h"
#include "Thread.h"
#include "WorkThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <memory>
using namespace std;
class MyTask:public wd::Task{
public:
    void process() override{
        srand(time(nullptr));
        int num=rand()%100;
        printf("make number is %d\n",num);
        sleep(1);
    }
};
void test(){
    wd::ThreadPool pool(4,10);
    pool.start();

    unique_ptr<wd::Task> ptask(new MyTask);

    int cnt=20;
    while(cnt--){
        pool.addTask(ptask.get());
    }

    pool.stop();

}

int main()
{
 test();
 return 0;
}
```

##### 序列图

<img src="D:\卓面\学习\王道学习笔记\类图\SequenceDiagram1.jpg" style="zoom: 67%;" />

std::function 函数的容器：统筹了c++中所有的函数形式。

普通函数，函数指针，静态成员函数，非静态成员函数，lambda表达式。

> [!IMPORTANT]
>
> **Question: 什么是左值和右值？**
>
> 左值可以取地址，右值不可以取地址。 
>
> 取地址即可以在内存空间中找到存放的地址。
>
> <font color='red'>**注：**</font>普通函数的函数名就是一个地址值，可以将其看成一个常量。虽然可以取地址，但是函数名不是左值。

#### 8.基于对象的线程实现

##### 类图

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250828153811799.png" alt="image-20250828153811799" style="zoom:67%;" />

##### 实现代码

```c++
//Thread.h
#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>
#include <functional>
namespace wd{

using ThreadCallback=std::function<void ()>;
class Thread{
public:
    Thread(ThreadCallback &&);
    void start();
    void join();
    static void * start_routine(void *);

private:
    pthread_t      _pthid;
    bool           _isrunning;
    ThreadCallback _cb;
};
} 
#endif
```



```c++
//Thread.cc
#include "Thread.h"
#include <string.h>
#include <stdio.h>
namespace wd{

Thread::Thread(ThreadCallback &&cb)
:_pthid(0)
,_isrunning(false)
,_cb(std::move(cb))
{

}

void Thread::start(){
    if(!_isrunning){
        int ret=pthread_create(&_pthid,NULL,start_routine,this);
        if(ret!=0){
            fprintf(stderr,"%s\n",strerror(ret));
        }
    }
    _isrunning=true;
}

void Thread::join(){
    if(_isrunning){
        pthread_join(_pthid,NULL);
        _isrunning=false;
    }
}

void * Thread::start_routine(void *arg){
    Thread* pth=static_cast<Thread *>(arg);

    if(pth){
        pth->_cb();
    }
    return NULL;
}
}

```

```c++
//测试文件
#include "Thread.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <functional>
#include <memory>

using namespace std;

/* class MyTask{ */
/* public: */
void run(){
    srand(time(nullptr));
    int cnt=10;
    while(cnt--){
        sleep(1);
        int num=rand()%100;
        printf("sub thread make a number is %d\n",num);
    }

}
/* }; */
void test(){
    unique_ptr<wd::Thread> thread(new wd::Thread(run));
    thread->start();
    thread->join();

}

int main()
{
 test();
 return 0;
}
```

#### 9.基于对象的线程池的实现

##### 类图：

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250828205836142.png" alt="image-20250828205836142" style="zoom:67%;" />

##### 代码实现：

```c++
//TaskQueue.h
#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H
#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

using std::function;
namespace wd{
using ElemType=function<void ()>;
class TaskQueue{
public:
    TaskQueue(int);
    bool empty();
    bool full();
    void push(ElemType &&);
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
```

```c++
//TaskQueue.cc
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

void TaskQueue::push(ElemType &&taskcb){
    _mutex.lock();

    while(full()){
        _notFull.wait();
    }

    _que.push(std::move(taskcb));
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
```

```c++
//ThreadPool.h
#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include "Thread.h"
#include "TaskQueue.h"
#include <vector>
#include <memory>
#include <functional>

using std::vector;
using std::unique_ptr;
using std::function;

namespace wd{

using Funtask=function<void ()>;

class ThreadPool{
public:
    ThreadPool(int,int);
    ~ThreadPool();
    void start();
    void stop();
    void addTask(Funtask &&);
    void doTask();
private:
    vector<unique_ptr<Thread>> _threads;
    TaskQueue                  _taskqueue;
    int                        _threadnum;
    bool                       _isExit;
};
}

#endif
```

```c++
//ThreadPool.cc
#include "ThreadPool.h"
#include <unistd.h>
#include <functional>

using std::bind;
namespace wd{
ThreadPool::ThreadPool(int threadnum,int quesize)
:_threads()
,_taskqueue(quesize)
,_threadnum(threadnum)
,_isExit(false)
{
    _threads.reserve(_threadnum);
}
ThreadPool::~ThreadPool(){
    if(!_isExit){
        stop();
    }
}
void ThreadPool::start(){
    for(int i=0;i<_threadnum;++i){
        unique_ptr<Thread> thread(new wd::Thread(bind(&ThreadPool::doTask,this)));
        _threads.push_back(std::move(thread));
    }

    for(auto &th:_threads){
        th->start();
    }
}

void ThreadPool::stop(){
    while(!_taskqueue.empty()){
        sleep(1);
    }

    _isExit=true;
    _taskqueue.wake();

    for(auto &th:_threads){
        th->join();
    }
}

void ThreadPool::addTask(Funtask &&ptask){
    if(ptask){
        _taskqueue.push(std::move(ptask));
    }
}

void ThreadPool::doTask(){
    while(!_isExit){
        Funtask ptask=_taskqueue.pop();
        if(ptask){
            ptask();
        }
    }    
}
}
```

```c++
//TestThreadPool.cc
#include "ThreadPool.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <functional>
#include <memory>

using std::bind;
using std::unique_ptr;

class Task{
public:
void process(){
        srand(time(nullptr));
        int num=rand()%100;
        printf("make a number is %d\n",num);
        sleep(1);
}
};
void test(){

    unique_ptr<Task> ptask(new Task());
    wd::ThreadPool pool(4,10);
    pool.start();

    int cnt=10;
    while(cnt--){
        pool.addTask(bind(&Task::process,ptask.get()));
    }

    pool.stop();
}

int main()
{
 test();
 return 0;
}
```

