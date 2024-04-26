#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

//定义进程结构体
struct Process
{
    int id;
    int priority;
    int brust_time;

    Process(int id,int priority,int brust_time):id(id),priority(priority),brust_time(brust_time){};
    bool operator<(const Process& other)const{
        return priority>other.priority;//最小堆，所以这里用大于符号
    }//省略了this指针，通过重载小于运算符达到定义结构体间大小比较的目的
};

//定义进程调度器
class ProcessScheduler
{
private:
    std::priority_queue<Process>ready_queue;//就绪队列，使用最小堆实现
public:
    //添加进程到就绪队列
    void add_process(int id,int priority,int brust_time){
        Process process(id,priority,brust_time);
        ready_queue.push(process);
    }
    //执行进程调度
    void scheduler(){
        while(!ready_queue.empty()){
            Process current_process=ready_queue.top();
            ready_queue.pop();
            std::cout<<"Excuting process"<<current_process.id<<"with priority"<<current_process.priority<<"and burst time"
            <<current_process.brust_time<<std::endl;
            //模拟进程执行
            for(int i=0;i<current_process.brust_time;i++){
                std::cout<<".";
            }
            std::cout<<std::endl;
        }
    }
};
int main(){
    ProcessScheduler scheduler;
    scheduler.add_process(1,3,5);
    scheduler.add_process(2,1,2);
    scheduler.add_process(3,4,1);
    scheduler.scheduler();
    return 0;
}



