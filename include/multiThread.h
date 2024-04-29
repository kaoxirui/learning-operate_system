#ifndef _MULTITHREAD_H
#define _MULTITHREAD_H
#include<iostream>
#include<mutex>
#include<queue>
#include<condition_variable>
using namespace std;
const int BUFFER_SIZE=10;
class SharedBuffer{
private:
    mutex mutex_;
    queue<int>buffer_;
    condition_variable not_empty_;
    condition_variable not_full_;
public:
    SharedBuffer():buffer_(),mutex_(),not_empty_(),not_full_(){}
    //生产者生产数据
    void produce(int data){
        unique_lock<mutex>lock(mutex_);//为保证条件变量不会因为多线程混乱，所以先加锁
        not_full_.wait(lock,[this]{return buffer_.size()<BUFFER_SIZE;});//等待缓冲区有位置
        buffer_.push(data);
        lock.unlock();
        not_empty_.notify_one();//通知消费者缓冲区非空
    }
    //消费者消费数据
    int consume(){
        unique_lock<mutex>lock(mutex_);
        not_empty_.wait(lock,[this]{return !buffer_.empty();});//等待缓冲区有资源可用
        int data=buffer_.front();
        buffer_.pop();
        lock.unlock();
        not_full_.notify_one();
        return data;
    }
};


#endif