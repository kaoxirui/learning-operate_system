#include"jobsecheduler.h"

int main(){
    JobSecheduler jobsecheduler;
    jobsecheduler.addJob(Job(1,3,5));
    jobsecheduler.addJob(Job(2,1,2));
    jobsecheduler.addJob(Job(3,4,3));
    Job* job;
    while ((job=jobsecheduler.schedule())!=nullptr)
    {
        //
    }
    for(const auto&job:jobsecheduler.getJobhistory()){
        cout<<"job"<<job.jobid<<"turnaround time="<<job.turnaroundTime<<endl;
    }
    return 0;
    
}