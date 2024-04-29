#include"multiThread.h"
#include<thread>
using namespace std;
void producer(SharedBuffer& buffer,int id){
    for(int i=0;i<5;++i){
        this_thread::sleep_for(chrono::seconds(1));
        buffer.produce(100*id+i);
        cout<<"Producer "<<id<<"produced "<<100*id+i<<endl;
    }
}

void consumer(SharedBuffer& buffer,int id){
    for(int i=0;i<5;++i){
        int data=buffer.consume();
        this_thread::sleep_for(chrono::seconds(1));
        cout<<"Consumer "<<id<<"consumes "<<data<<endl;
    }
}

int main(){
    SharedBuffer buffer;
    thread producer1(producer,ref(buffer),1);
    thread producer2(producer,ref(buffer),2);
    thread consumer1(consumer,ref(buffer),1);
    thread consumer2(consumer,ref(buffer),2);
    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();
    return 0;
}