#include "ThreadPool.h"
#include "Task.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <memory>

using std::unique_ptr;
class MyTask:public wd::Task{
public:
    void process() override{
        srand(time(nullptr));
        int num=rand()%100;
        printf("make a number is %d\n",num);
        sleep(1);
    }
};
void test(){
    unique_ptr<wd::Task> task(new MyTask);

    wd::ThreadPool pool(4,10);
    pool.start();

    int cnt=10;
    while(cnt--){
        pool.addTask(task.get());
    }

    pool.stop();
}

int main()
{
 test();
 return 0;
}

