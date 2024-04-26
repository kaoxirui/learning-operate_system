#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H
#include<mutex>
#include<condition_variable>

using namespace std;

class Semaphore{
public:
    Semaphore(long count=0):count(count){}
    //V操作，唤醒
    void signal(){
        unique_lock<mutex>unique(mt);//对互斥量加锁
        ++count;
        if(count<=0)
            cond.notify_one();//用来通知一个等待线程，表示某个条件已经满足，从而唤醒等待线程继续执行
    }
    //P操作，等待
    void wait(){
        unique_lock<mutex>unique(mt);
        --count;
        if(count<0){
            cond.wait(unique);
        }
    }
private:
    mutex mt;//创建一个互斥量
    condition_variable cond;
    long count;
};
#endif