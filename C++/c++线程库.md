## c++线程库

### 1.基本概念

vim 进程状态查看命令：ps -aux

进程是资源拥有的基本单位，线程可以看成是轻量级的进程，线程是调度或执行的基本单位。

一个进程中至少有一个线程，main线程，也就是主线程。

为了区分不同的进程和线程，会给每个进程或者线程一个全局的唯一标识符，称为：进程id或者线程id。

进程或者线程都会有状态，比如：运行，睡眠，阻塞。

进程或者线程启动的目的，就是为了做任务。进程或者线程做任务，其实就是指向对应的函数，可以将这种函数称为入口函数。

线程一旦创建出来之后，它的执行是随机的，谁先执行，谁后执行，谁执行的快，谁执行的慢，这些都是随机的。

不同的平台上面，使用进程或者线程的接口不一样，windows与Linux都有自己的函数接口，在c++11中的线程库，是跨平台的，也就是说可以在不同的操作系统上使用。

### 2.线程的构造函数

```C++
thread() noexcept;//1、构建无参对象

thread(thread&& other) noexcept;//2、移动构造函数

template< class Function, class... Args >
explicit thread(Function&& f, Args&&... args);//3、传递入口函数f，并且该函数的参数是可变的(thread的传参方式与bind//非常类似的，所以可以传占位符，默认传递方式是值传递)

thread(const thread&) = delete;//4、不支持拷贝操作（不具备复制控制语义）
```

1/2/3/...+shift+K进入man手册,前面的数字为man手册的卷数。q退回。

### 3.线程的执行概念

三种主线程等待子线程的方法while,sleep,join，但是更建议使用join方法，只要子线程没有执行完，那么主线程一直等着子线程。

#### 1.线程id

在thread类中，有成员函数get_id可以获取线程的标识符。

还可以调用std：：this_thread中的get_id函数获取线程id。

#### 2.线程的等待

为了让线程对象有足够的时间进行执行，所以可以调用join方法。

#### <font color='red'>3.线程入口函数的传递方式</font>

##### 普通函数

```c++
#include <iostream>
#include <thread>
using namespace std;
void threadfunc(int x){
    cout<<"threadfunc"<<endl;
    ++x;
    cout<<"x="<<x<<endl;
}

int main()
{
    cout<<"start main"<<endl;
    thread th(threadfunc,10);
    th.join();
    cout<<"end main"<<endl;
    return 0;
}
```

![image-20250808140041421](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250808140041421.png)

##### 函数指针

```C++
void threadfunc(int x){
    cout<<"threadfunc"<<endl;
    ++x;
    cout<<"x="<<x<<endl;
}
int main(){
    cout<<"start main"<<endl;
    void (*pfunc)(int)=threadfunc;
    thread th(pfunc,10);
    th.join();
    cout<<"end main"<<endl;
    return 0;
}
```

##### 函数引用

```C++
void threadfunc(int x){
    cout<<"child thread_id"<<this_thread::get_id()<<endl;
    ++x;
    cout<<"x="<<x<<endl;
}
int main(){
    cout<<"start main"<<endl;
    cout<<"main thread_id:"<<this_thread::get_id()<<endl;
    void (&pfunc)(int)=threadfunc;
    thread th(pfunc,10);
    cout<<"child thread_id"<<th.get_id()<<endl;
    th.join();
    cout<<"end main"<<endl;
    return 0;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250808140937107.png" alt="image-20250808140937107" style="zoom:67%;" />

##### 成员函数

```C++
class Example{
public:
    void threadfunc(int x){
        cout<<"child thread_id:"<<this_thread::get_id()<<endl;
        ++x;
        cout<<"x="<<x<<endl;
    }
};
int main(){
    cout<<"start main"<<endl;
    cout<<"Main thread_id:"<<this_thread::get_id()<<endl;
    Example ex;
    thread th(&Example::threadfunc,&ex,10);
    cout<<"child thread_id:"<<th.get_id()<<endl;
    th.join();
    cout<<"end main"<<endl;
    return 0;
}
```

##### **函数对象**

```C++
class Example{
public:
    void operator()(int x){
        cout<<"child thread_id:"<<this_thread::get_id()<<endl;
        ++x;
        cout<<"x="<<x<<endl;
    }
};
int main(){
    cout<<"start main"<<endl;
    cout<<"Main thread_id:"<<this_thread::get_id()<<endl;
    Example ex;
    thread th(ex,10);
    cout<<"child thread_id:"<<th.get_id()<<endl;
    th.join();
    cout<<"end main"<<endl;
    return 0;
}
```



##### **lambda表达式（常用）**

```c++
int main(){
    cout<<"start main"<<endl;
    cout<<"main thread_id:"<<this_thread::get_id()<<endl;
    thread th([](int x){
              cout<<"child thread_id:"<<this_thread::get_id()<<endl;
              ++x;
              cout<<"x="<<x<<endl;
              },10);
    th.join();
    cout<<"end main"<<endl;
    return 0;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250808142156748.png" alt="image-20250808142156748" style="zoom:80%;" />

##### **function**

```C++
int main(){
    cout<<"start main"<<endl;
    cout<<"main thread_id:"<<this_thread::get_id()<<endl;
    function<void(int)> fun=[](int x){
              cout<<"child thread_id:"<<this_thread::get_id()<<endl;
              ++x;
              cout<<"x="<<x<<endl;
    };
    thread th(fun,10);
    th.join();
    cout<<"end main"<<endl;
    return 0;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250808193505408.png" alt="image-20250808193505408" style="zoom:80%;" />

##### **bind（常用）**

```c++
void threadfunc(int x){
    cout<<"child thread_id:"<<this_thread::get_id()<<endl;
    ++x;
    cout<<"x="<<x<<endl;
}
int main()
{
    cout<<"start main"<<endl;
    cout<<"main thread_id:"<<this_thread::get_id()<<endl;
    function<void(int)> func=bind(threadfunc,10);
    thread th(func,10);
    th.join();
    cout<<"end main"<<endl;
    return 0;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250808194001654.png" alt="image-20250808194001654" style="zoom:80%;" />

##### 总结

线程入口函数的传递方式有很多，但是最终归结为一点，就是传递函数对象（也可以将其称为可调用对象）。

### 4.锁机制

#### std::mutex锁

```C++
//构造函数
constexpr mutex() noexcept;//无参的
mutex( const mutex& ) = delete;//拷贝构造函数被删除了

//上锁函数
void lock();

//解锁函数
void unlock();
```

注意：对于std::mutex而言，具备上锁与解锁的功能，因为锁只有两种状态，要么上锁了，要么解锁了（没有上锁一半或者解锁一半的概念），上锁与解锁要成对出现，不能连续两次上锁或者解锁，也就是要保证一次上锁对应一次解锁。

```C++
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
int global_cnt=0;
mutex mtx;
void threadfunc(){
    for(int i=0;i<1000000;++i){
       mtx.lock();
        ++global_cnt;
        mtx.unlock();
    }
}
void test(){
    thread th1(threadfunc);
    thread th2(threadfunc);
    th1.join();
    th2.join();
    cout<<global_cnt<<endl;
}

int main()
{
 test();
 return 0;
}
```

#### lock_guard锁

```C++
//构造函数
explicit lock_guard( mutex_type& m );

lock_guard(mutex_type &m, std::adopt_lock_t t );

lock_guard( const lock_guard &) = delete;
```

使用了RAII的思想：利用栈对象的生命周期管理资源

1.在构造函数中初始化资源

2.在析构函数中释放资源

3.提供若干个访问资源的访问方法

4.一般不允许复制或者赋值（对象语义）

**特点**：

- 构造时必须获取锁（通过 `mutex::lock()`），析构时自动释放锁（调用 `mutex::unlock()`）。
- 生命周期内始终持有锁，无法手动解锁或重新加锁。
- 不支持移动语义（无法转移所有权），也不能默认构造。

**适用场景**：

- 临界区范围明确且简单（从锁创建到作用域结束）。
- 不需要中途解锁或灵活控制锁的情况。

**优点：**不会死锁

**缺点：**不灵活

```c++
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
int global_cnt=0;
mutex mtx;//初始化互斥锁
void threadfunc(){
    for(int i=0;i<1000000;++i){
        lock_guard<mutex> lg(mtx);
        ++global_cnt;
    }
}
void test(){
    thread th1(threadfunc);
    thread th2(threadfunc);
    th1.join();
    th2.join();
    cout<<global_cnt<<endl;
}

int main()
{
 test();
 return 0;
}
```

#### unqiue_lock锁

使用了RAII的思想，利用栈对象的生命周期管理资源。在构造函数加锁，析构函数解锁。

**特点**：

- 构造时可以选择是否立即获取锁（支持延迟加锁）。
- 支持手动解锁（`unlock()`）和重新加锁（`lock()`）。
- 支持移动语义（可转移锁的所有权），但不可复制。
- 可以配合 `std::condition_variable` 使用（必须用 `unique_lock`）。

**适用场景**：

- 需要中途解锁（例如临界区中间有耗时操作，可暂时释放锁让其他线程执行）。
- 需要延迟加锁（先创建锁对象，稍后再获取锁）。
- 需要将锁的所有权传递给其他函数或线程。
- 与条件变量（`condition_variable`）配合使用（强制要求）。

```c++
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
int global_cnt=0;
int global_cnt2=0;
mutex mtx;//初始化互斥锁
void threadfunc(){
    for(int i=0;i<1000000;++i){
        unique_lock<mutex> ul(mtx);
        ++global_cnt;
        ul.unlock();//提前解锁
        ++global_cnt2;
    }
}
void test(){
    thread th1(threadfunc);
    thread th2(threadfunc);
    th1.join();
    th2.join();
    cout<<"global_cnt="<<global_cnt<<endl;
    cout<<"global_cnt2="<<global_cnt2<<endl;
}

int main()
{
 test();
 return 0;
}
```

![image-20250808201558583](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250808201558583.png)

#### 总结

lock_guard与unique_lock都使用了RAII思想，利用栈对象的生命周期管理资源，lock_guard不能人为手动解锁与上锁，但是unique_lock提供了人为上锁与解锁的接口，所以unique_lock比lock_guard更加灵活一些，但是lock_guard在效率上，比unique_lock要高。

### 5.条件变量

条件变量类是一个同步原语，它可以在同一时间阻塞一个线程或者多个线程，直到其它线程改变了共享变量并通知。

**<font color='red'>它必须跟互斥锁一起配合使用</font>**，条件变量之所以要和互斥锁一起使用，主要是因为互斥锁的一个明显的特点就是它只有两种状态：锁定和非锁定，而条件变量可以通过允许线程阻塞和等待另一个线程发送信号来弥补互斥锁的不足，所以互斥锁和条件变量通常一起使用。

条件变量本身不是锁，但它也可以造成线程阻塞，通常与互斥锁配合使用，给多线程提供一个会合的场所。

```C++
//构造函数
condition_variable();//无参的
condition_variable(const condition_variable&) = delete;//拷贝构造函数被删除了

//睡眠(可以让线程在条件变量上睡眠)
void wait( std::unique_lock<std::mutex>& lock );

template< class Predicate >
void wait( std::unique_lock<std::mutex>& lock, Predicate pred );

//唤醒函数（将在条件变量上睡眠的线程唤醒）
void notify_one()；//唤醒条件变量上的一个线程
void notify_all()；//唤醒条件变量上的所有线程
```

### 6.生产者消费者模型

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250808213211288.png" alt="image-20250808213211288" style="zoom:50%;" />

```C++
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <time.h>
#include <thread>
#include <chrono> 
using namespace std;
class TaskQueue{
private:
    int _capacity;
    queue<int> que;
    mutex mtx;
    condition_variable isproduce;
    condition_variable isconsume;
public:
    TaskQueue(int cap)
    :_capacity(cap)
    {

    }
    bool full(){
        return _capacity==que.size();
    }
    bool empty(){
        return 0==que.size();
    }
    void push(const int value){
        //1.先获取锁
        unique_lock<mutex> ul(mtx);
        //2.判断当前容器是否满
        if(full()){
            //如果满了，让生产者在条件变量上睡眠
            isproduce.wait(ul);
        }
        //不满，将数据加入容器，并唤醒消费者
        que.push(value);
        isconsume.notify_one();
    }
    int pop(){
        //1.先获取锁
        unique_lock<mutex> ul(mtx);
        //2.判断是否有产品
        if(empty()){
            //如果没有产品，让消费者在条件变量上睡眠
            isconsume.wait(ul);
        }
        //有产品，取出产品消费，并通知生产者
        int temp=que.front();
        que.pop();
        isproduce.notify_one();
        return temp;
    }
};
class Producer{
public:
    void produce(TaskQueue &taskqueue){
        srand(clock());
        for(int i=0;i<10;++i){
            int number=rand()%100;
            taskqueue.push(number);
            cout<<"第"<<i+1<<"个"<<"produce>>"<<number<<endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};
class Consumer{
public:
    void consume(TaskQueue &taskqueue){
        for(int i=0;i<10;++i){
            int number=taskqueue.pop();
            cout<<"第"<<i+1<<"个"<<"consume<<"<<number<<endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};
void test(){
    TaskQueue taskqueue(5);

    Producer pro;
    Consumer con;

    thread th1(&Producer::produce,pro,std::ref(taskqueue));
    thread th2(&Consumer::consume,con,std::ref(taskqueue));
    
    th1.join();
    th2.join();
}

int main()
{
 test();
 return 0;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250808213950222.png" alt="image-20250808213950222" style="zoom:50%;" />

由于生产者和消费者之间的速度不匹配，可能导致打印结果紊乱，可以通过阻塞线程来解决。

```C++
 std::this_thread::sleep_for(chrono::seconds(1));//阻塞线程1s
```

当前的代码在多生产者和多消费者时，存在**虚假唤醒**的问题。

```C++
void push(const int value){
        //1.先获取锁
        unique_lock<mutex> ul(mtx);
        //2.判断当前容器是否满
        while(full()){
            //如果满了，让生产者在条件变量上睡眠
            isproduce.wait(ul);
        }
        //不满，将数据加入容器，并唤醒消费者
        que.push(value);
        isconsume.notify_one();
    }
    int pop(){
        //1.先获取锁
        unique_lock<mutex> ul(mtx);
        //2.判断是否有产品
       while(empty()){
            //如果没有产品，让消费者在条件变量上睡眠
            isconsume.wait(ul);
        }
        //有产品，取出产品消费，并通知生产者
        int temp=que.front();
        que.pop();
        isproduce.notify_one();
        return temp;
    }
```

### 7.线程池

如果有一个任务就创建一个线程去处理这个任务，然后当任务执行完毕之后，就销毁线程，如果后续还有任务到来，那么就继续创建线程执行任务，当任务执行完毕之后，又销毁线程，那么如果任务量比较大，那么创建线程与销毁线程也会有很大开销，所以可以先创建一部分线程，然后等着接收任务，当任务执行完毕之后，线程不会立马销毁，而是继续执行其它的任务，这样就可以解决线程创建销毁带来的开销。

```C++

```

