### Qt线程

#### 1.两种线程的概念

gui线程：第一个线程是Gui线程，也称主线程或main线程，主线程负责几乎所有Gui操作。

子线程：所有其它的耗时操作，都是由QThread及其子类来完成，可以称为工作线程或者子线程。

如果子线程也想处理GUI相关的操作，那么就可以与GUI线程进行信号与槽的连接，这样两者就可以进行通信。

#### 2.使用线程的条件

处理耗时操作

保持界面响应

处理并发任务

#### 3.Qt线程相关函数

##### 3.1 线程启动

```c++
[slot] void QThread::start(QThread::Priority priority = InheritPriority);
//QThread::Priority枚举类型:
//QThread::IdlePriority          没有其它线程运行时才调度
//QThread::LowestPriority        比LowPriority调度频率低
//QThread::LowPriority           比NormalPriority调度频率低
//QThread::NormalPriority        操作系统的默认优先级
//QThread::HighPriority          比NormalPriority调度频繁
//QThread::HighestPriority       比HighPriority调度频繁
//QThread::TimeCriticalPriority  尽可能频繁的调度
//QThread::InheritPriority       使用和创建线程同样的优先级. 这是默认值
```

线程的启动函数，调用该函数后会执行run方法，但在run函数执行前会触发started信号。

##### 3.2 线程优先级

```C++
void QThread::setPriority(QThread::Priority priority);
//QThread::Priority枚举类型:
//QThread::IdlePriority          没有其它线程运行时才调度
//QThread::LowestPriority        比LowPriority调度频率低
//QThread::LowPriority           比NormalPriority调度频率低
//QThread::NormalPriority        操作系统的默认优先级
//QThread::HighPriority          比NormalPriority调度频繁
//QThread::HighestPriority       比HighPriority调度频繁
//QThread::TimeCriticalPriority  尽可能频繁的调度
//QThread::InheritPriority       使用和创建线程同样的优先级. 这是默认值
```

##### 3.3 线程执行

```C++
[protected]int QThread::exec()
```

该函数的作用是进入事件循环并等待直到调用exit函数，返回值是通过调用exit函数来获得，如果调用成功则返回0

```c++
[virtual protected] void QThread::run();
```

线程的运行起点，在调用start函数之后，新创建的线程就会调用这个函数，底层默认调用exec函数，大多数需要重写这个函数，便于管理自己的线程，该方法返回时，该线程执行将结束。

##### 3.4 线程退出

```C++
[slot] void QThread::quit();
void QThread::exit(int returnCode=0);
```

这两种方式都可以让线程退出事件循环，quit调用成功等价于执行了exit(0)，这两种方式是让线程优雅退出的方式。

```C++
[slot] void QThread::terminate();
```

终止线程，线程可能会立即终止也可能不会，这取决于操作系统的调度策略，使用terminate之后再使用QThread::wait（）,以确保万无一失。

警告：此函数比较危险，不鼓励使用。线程可以在代码执行的任何点被终止。线程可能在更新数据时被终止，从而没有机会来清理自己，解锁等等。总之，只有在绝对必要时使用此函数。

```C++
void QThread::requestInterruption();
```

请求线程停止执行，但它不会强制终止线程，而是设置线程的中断标志。此函数不停止线程上运行的任何事件循环，并且在任何情况下都不会终止它。

##### 3.5 线程的等待

```C++
//线程将会被阻塞等待time毫秒。如果线程退出，则wait会返回。Wait函数解决多线程在执行时序上的依赖。
bool wait(unsigned long time = ULONG_MAX);

//线程睡眠msecs毫秒
[static] void QThread::msleep(unsigned long msecs);
//线程睡眠secs秒
[static] void QThread::sleep(unsigned long secs); 
//线程睡眠usecs微秒
[static] void QThread::usleep(unsigned long usecs); 
```

##### 3.6 线程的状态

```C++
//判断线程是否结束
bool isFinished() const;   

//判断线程是否正在运行
bool isRunning() const;  

//如果线程上的任务运行应该停止，返回true。注意：此函数可用于使长时间运行的任务干净地中断。从不检查或作用于该函数返回值是安全的，但是建议在长时间运行的函数中经常这样做。注意：不要过于频繁调用，以保持较低的开销。
bool isInterruptionRequested() const;
```

##### 3.7 线程的标识

```C++
//返回一个线程指针
[static] QThread *QThread::currentThread();

//返回当前正在执行的线程的id
[static] Qt::HANDLE QThread::currentThreadId();
```

##### 3.8 线程的属性

```C++
//设置或者获取优先级
void QThread::setPriority(QThread::Priority priority);
QThread::Priority priority() const;

//设置或者获取线程堆栈大小
void QThread::setStackSize(uint stackSize);
uint QThread::stackSize() const;

//根据启用的参数启用或禁用当前线程的终止。该线程必须由QThread启动。
void setTerminationEnabled ( bool enabled = true );  
```

##### 3.9 线程的信号

```C++
//启动线程运行会触发该信号
[signal] void QThread::started();

//终止线程运行会触发该信号
[signal] void QThread::finished();
```

#### 4.Qt线程的使用

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250822135930500.png" alt="image-20250822135930500" style="zoom:67%;" />

在Qt中，常用的使用线程的方法有如下两种：

- 继承QThread类，重写run()函数；
- 继承QObject类，通过moveToThread(thread)，交给thread执行。

##### 4.1 重写run方法

在Qt中，因为QThread类本身并不执行任何的任务，主要就是提供线程管理的功能，比如：启动、停止、暂停和恢复线程，而run函数是虚函数，所以自己写的线程类需要重写该虚函数，并且在该虚函数中定义自己将要执行的具体任务。

<span style=color:red;background:yellow;font-size:20px>常规步骤如下</span>：

- 自定义⼀个类，继承自QThread；

- 重写run方法（也称线程处理函数，和主线程不是同⼀个线程），并在其中实现需要执行的复杂逻辑；

- 调用start函数实现线程启动，注意：线程启动不能直接调用run函数；

```C++
#include "workthread.h"
#include <QDebug>
workthread::workthread()
{

}

workthread::~workthread()
{

}

void workthread::run()
{
    qDebug()<<"workthread is Runing";
    qDebug()<<"workthreadid:"<<QThread::currentThreadId();

    for(int i=0;i<10;++i){
        QThread::sleep(1);
        qDebug()<<"workthread run i="<<i;
    }
}


#include "widget.h"
#include "workthread.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    qDebug()<<"mainthreadid:"<<QThread::currentThreadId();
    //1.创建线程
    workthread work;

    QObject::connect(&work,&workthread::started,[](){
        qDebug()<<"线程启动触发了started";
    });

    QObject::connect(&work,&workthread::finished,[&](){
        qDebug()<<"线程结束触发了finished";
        a.quit();
        //w.close();
    });

//    2.启动线程
    work.start();

    return a.exec();
}

```

##### 4.2、使用moveToThread迁移

<span style=color:red;background:yellow;font-size:20px>常规步骤如下</span>：

- 自定义类并继承自QObject类；
- 创建自定义类的对象，<span style=color:red;background:yellow>注意不能指定父对象</span>；
- 创建QThread类的对象，可以指定其父对象；
- 调用moveToThread函数，将自定义对象加入到QThread的对象中；
- 使用信号与槽触发任务（通过信号与槽机制跨线程通信）；
- 使用deleteLater函数自动清理资源（或者其他方式清理资源）；
- 调用start函数启动线程；

注意：调用start函数只是启动了线程，但是并没有开启线程处理函数，线程处理函数的开启需要用到信号槽机制。还有就是moveToThread要在start之前。

```C++
#include "mythread.h"
#include <QDebug>
#include <QThread>
MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::dotask()
{
    qDebug()<<"MyThread ID:"<<QThread::currentThreadId();
    for(int i=0;i<10;++i){
        QThread::sleep(1);
        qDebug()<<"MyThread Data:"<<i;
    }
    emit signalQuit();
}
#include "widget.h"

#include <QApplication>
#include "mythread.h"
#include <QThread>
#include <QObject>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    qDebug()<<"MainThread ID:"<<QThread::currentThreadId();
    MyThread *work=new MyThread;
    QThread *thread=new QThread;

    //将自定义对象加入QThread对象中
    work->moveToThread(thread);

    QObject::connect(thread,&QThread::started,work,&MyThread::dotask);
    QObject::connect(work,&MyThread::signalQuit,thread,&QThread::quit);

    QObject::connect(thread,&QThread::finished,work,&MyThread::deleteLater);
    QObject::connect(thread,&QThread::finished,thread,&QThread::deleteLater);
    QObject::connect(thread,&QThread::finished,[&](){
        qDebug()<<"线程结束触发了finished信号";
        a.quit();//关闭窗口
    });

    //启动线程
    thread->start();

    qDebug()<<"QThread ID:"<<thread->currentThreadId();
    return a.exec();
}

```

##### 4.3 两种方式的对比总结

重写run方法的形式，非常简单，但是灵活性比较差，扩展性比较差。

moveToThread的方法灵活性比较强，可以在同一类中处理大量不同的任务，线程与任务分离的操作，此方式是Qt官方推荐的方式，但是该方式的代码比较复杂。

#### 5.Qt的锁机制

##### 5.1 QMutex锁

```c++
#include <QMutex>
//构造函数
QMutex(QMutex::RecursionMode mode);
//QMutex::RecursionMode枚举：
//QMutex::Recursive 递归，允许多次加锁，但要有对应的多次解锁
//QMutex::NonRecursive 非递归，只能加锁一次

//无参构造
QMutex();

//上锁
void lock();
//解锁
void unlock();
```

##### 5.2 读写锁

可以允许多个读者同时读数据，但只能有一个写，并且写读操作不能同时进行  

```c++
QReadWriteLock(QReadWriteLock::RecursionMode recursionMode = NonRecursive);

void lockForRead();
void lockForWrite();
bool tryLockForRead();
bool tryLockForRead(int timeout);
bool tryLockForWrite();
bool tryLockForWrite(int timeout);
void unlock();
```

```C++
QReadWriteLock lock;
void ReaderThread::run()
{
    lock.lockForRead();
    read_file();//读文件
    lock.unlock();
}
 
void WriterThread::run()
{
    lock.lockForWrite();
    write_file();//写文件
    lock.unlock();
}
```

#### 6.信号量

在多线程环境中，多个线程可能需要访问有限的共享资源。如果没有适当的同步机制，就可能出现多个线程同时访问同一资源的情况，导致数据损坏或不一致。Qt提供了QSemaphore类来实现信号量。QSemaphore类提供了以下基本操作：

- acquire(int n)：尝试获取n个信号量。如果信号量的值小于n，则调用线程将被阻塞，直到信号量的值足够大。

- release(int n)：释放n个信号量，增加信号量的计数器。

- available()：返回当前可用的信号量数量。

  

#### 7.条件变量

在多线程环境中，线程可能需要等待某个条件成立才能继续执行，在Qt中使用QWaitCondition表示条件变量。

```C++
QWaitCondition();

void notify_all();
void notify_one();
void wakeAll();
void wakeOne();

bool wait(QMutex *lockedMutex, unsigned long time = ULONG_MAX);
bool wait(QReadWriteLock *lockedReadWriteLock, unsigned long time = ULONG_MAX);
```

