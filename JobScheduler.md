# 作业调度算法

## 三个阶段和三个状态

收容阶段->运行阶段->完成阶段

后备状态->运行状态->完成状态


* 收容阶段：操作员把用户提交的作业通过某种方式或SPOOLiing 系统输入到硬盘上，再为该作业建立 JCB ，并把它放入都作业后备队列中。此时作业状态为 后备状态 。

* 运行阶段：当作业被作业调度选中后，便为它分配必要的资源和建立进程，并把它放入就绪队列。此时作业的状态为就绪状态，但作业可能多次在就绪状态和运行状态之间转换，所以，在一个作业从第一次进入就绪状态开始，直到运行结束，此期间的作业状态为 运行状态。

* 完成阶段：当作业运行完成、或发生异常情况而提前结束时，作业便进入完成阶段，系统中的“终止作业”程序将会回收已分配给该作业的作业控制块和所有资源。此时作业的状态为 完成状态。

## 常见算法
先来先服务（FCFS）、短作业优先（SJF）、优秀级调度算法（PSA）、高响应比优先调度算法（HRRN）、时间片轮转（RR）、多级反馈队列算法。