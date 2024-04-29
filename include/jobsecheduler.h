#ifndef _JOBSECHEDULER_H
#define _JOBSECHEDULER_H

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
struct Job
{
    int jobid;//作业id
    int priority;//优先级
    int brustTime;//执行时加
    int waitTime;//等待时间
    int turnaroundTime;//周转时间，包括了作业在就绪队列中等待时间和实际执行时间
    Job(int id,int prio,int brust):jobid(id),priority(prio),brustTime(brust),waitTime(0),turnaroundTime(0){}

    bool operator<(const Job& other)const{
        return priority<other.priority;//优先级越高在队列中越靠前
        //如果当前作业对象的优先级（priority）小于传入的另一个作业对象的优先级，则返回 true，否则返回 false。
    }
};

class JobSecheduler
{
private:
    int currentTime;//当前时间
    priority_queue<Job>readQueue;//就绪队列，使用优先级队列实现
    vector<Job>jobHistory;//作业历史记录
public:
    JobSecheduler():currentTime(0){}

    //添加作业到就绪队列
    void addJob(const Job& job){
        readQueue.push(job);
    }
    //执行调度，返回下一个要执行的作业
    Job* schedule(){
        if(readQueue.empty()){
            return nullptr;
        }
        Job currenJob=readQueue.top();//执行优先级最高的Job
        readQueue.pop();
        //更新等待时间和周转时间
        currenJob.waitTime=currentTime;
        currenJob.turnaroundTime=currenJob.waitTime+currenJob.brustTime;
        cout<<"Executing Job: "<<currenJob.jobid<<"with priority: "<<currenJob.priority<<",brust time:"<<currenJob.brustTime
        <<",wait time"<<currenJob.waitTime<<endl;
        currentTime+=currenJob.brustTime;
        jobHistory.push_back(currenJob);
        return &jobHistory.back();
    }

    int getCurrentTime()const{
        return currentTime;
    }
    const vector<Job>& getJobhistory()const{
        return jobHistory;
    }//返回常应用到vector<Job>，可以获取到jobHistory的副本，但无法通过返回的常引用来修改他
    //1. 安全访问内容 2. 避免了不必要的副本构造
};
#endif