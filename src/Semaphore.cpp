#include"semaphore.h"
#include<thread>
#include<iostream>
using namespace std;

Semaphore sem(0);

void funcA(){
    sem.wait();
    //do something
    cout<<"funcA"<<endl;
}

void funcB(){
    this_thread::sleep_for(chrono::seconds(1));
    //do something
    cout<<"funcB"<<endl;
    sem.signal();
}

int main(){
    thread t1(funcA);
    thread t2(funcB);
    t1.join();
    t2.join();
}
/*
想让funcB先执行，然后运行funcA，多线程是通过时间片轮询来执行的
假设先开始跑funcA，执行到sem.wait()的时候，进入wait函数可知，count-1，小于0，会发生阻塞，等待其他进程唤醒
然后切换到B，这里即是休眠了1s也不会iu切换到A，因为已经发生了阻塞，进入signal函数，count+1，小于0，会唤醒其他进程
*/