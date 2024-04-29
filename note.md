# 信号量
## 概念
**信号量机制**是一种有效的进程同步和互斥工具。信号量有整形，记录型，二进制型信号量等。常用整型信号量实现PV操作。P操作表示申请一个资源，V操作表示释放一个资源

信号量是一种特殊的变量，表现形式为一个整型S和一个队列

**信号量取值的意义**：S>=0时，表示某资源的可用数；S<0时，其绝对值表示阻塞队列中等待该资源的进程数

**P操作**：S=S-1，若S>=0，进程继续执行；若S<0,进程暂停执行，进入等待队列。即执行P操作时，有可用资源则继续执行，无可用资源则等待

**V操作**：S=S+1，若S>0，进程继续执行；若S<=0,唤醒等待队列中的一个进程。即执行V操作时，无等待进程则继续执行；有等待进程则唤醒该进程，然后本进程继续执行

**临界资源**：一次仅允许一个进程使用的资源。多个进程必须互斥地对它进行访问。在硬件方面有打印机、传真机等，软件方面有变量、缓冲区等。

**临界区**：每个进程中访问临界资源的那一段代码。每次只允许一个进程进入临界区，进入后不允许其他进程进入。

## PV操作处理相关问题
### 进程的互斥
所谓进程的互斥，指当一个进程（线程）进入临界区使用临界资源时，需要使用临界资源的其他进程（线程）必须等待。退出临界区后，需要使用该临界资源的进程解除阻塞。互斥是进程（线程）之间的间接制约关系。

```c++
P(信号量)
    临界区
V(信号量)
```

令信号量初值为1，进程进入临界区时执行P操作，信号量变为0，此时临界资源相当于被锁定，其他进程无法访问。然后执行V操作退出临界区，信号量变为1，临界资源得到释放，其他进程可以进行访问。

### 进程的同步
进程同步是指为完成某种任务而建立的两个及两个以上的进程在某些位置上因工作次序的需要而等待、传递信息所产生的直接制约关系，这种制约关系源于他们之间的合作关系（依赖关系）。所以同步是一种更为复杂的互斥。也就是说，进程同步就是进程（线程）的运行必须严格按照某种先后次序来运行，从而完成的特定的任务。

最简单的同步形式：进程A执行到L1时，依赖于进程B执行到L2时产生的数据。当进程A执行到L1时，如果进程B还未产生相应的数据，进程A只好等待进程B，只有进程B执行到L2计算出相应的结果后线程A在接着往下运行。

```c++
进程A     进程B
...       ...
L1：P()   L2:V()
...       ...
```

设置信号量初值为0，如果进程A先执行到L1，执行P操作后信号量小于0，A等待，直到B执行到L2执行V操作后，信号量为0，唤醒A继续执行。如果进程B先执行到L2，信号量+1，则进程A无需等待，直接就可以执行完

### 生产者与消费者问题（缓冲区问题）

* 生产者-消费者问题是指若干进程通过有限的共享缓冲区交换数据时的**缓冲区资源使用问题**。假设“生产者“进程不断向共享缓冲区写入数据（即生产数据）。而”消费者“进程不断从共享缓冲区读取数据（消费数据）；共享缓冲区共有n个，任何时刻只能有一个进程可对共享缓冲区进行操作

* 解决生产者与消费者进程的同步关系

* 处理缓冲区的互斥关系

#### 单缓冲区问题
可设置两个信号量S1，S2.S1的处值为1，表示缓冲区空余空间，S2处置为0，表示缓冲区产品个数

P1->生产一个产品->P(S1)->产品送缓冲区->V(S2)->P1

P2->P(S2)->从缓冲区取出一个产品->V(S1)->消费->P2

P1进程生产一个产品后，需要判断缓冲区是否有空间(对S1执行P操作时S1需要大于等于0)，如果有空间则产品可以放入缓冲区，缓冲区数量加一，需要对S2执行V操作。

P2进程消费产品，先判断缓冲区是否有产品(对S2执行P操作，S2需大于等于0)，如果有产品，则可以从缓冲区取出产品；从缓冲区取出一个产品，缓冲区空间加一，需要对S1执行V操作，然后消费者就可以消费了

当有多个生产者进程写入缓冲区、多个消费者进程读取缓冲区且每条消息只能读一次时，要考虑进程间的互斥关系，即同时只能有一个生产者向缓冲区写入一条消息，同时只能有一个消费者从缓冲区读取一条消息。互斥控制的要点在于判断出临界区的范围。



## std::unique_lock
为锁管理模板类，是对mutex的封装。**std::unique_lock对象以独占所有权的方式管理mutex对象的上锁和解锁操作，即在unique_lock对象的声明周期内，它所管理的锁对象会一直保持上锁状态；而unique_lock的声明周期结束后，他所管理的锁对象会被解锁**

```c++
#include <mutex>

std::mutex mutex;  // 创建一个互斥量

{
    std::unique_lock<std::mutex> lock(mutex);  // 对互斥量进行加锁

    // 在互斥量保护的临界区内执行一些操作
    // ...

}  // 在作用域结束时，unique_lock 的析构函数会自动解锁互斥量
```

当一个线程需要访问共享资源时，它会尝试获取锁。如果没有其他线程持有该锁，那么该线程成功获取锁，可以安全地访问共享资源。如果有其他线程已经持有锁，那么当前线程就会被阻塞，直到锁被释放。

锁的实现机制通常依赖于底层操作系统提供的原语，如互斥量、原子操作、条件变量等。具体实现细节可能因操作系统和编程语言而异。

## 条件变量

一种用于等待的同步机制，能阻塞一个或多个线程，直到收到另外一个线程发出的通知时，才会唤醒当前阻塞的线程。**与互斥量配合起来使用**

### 成员函数

`condition_variable`的成员函数主要分为两个部分：`线程等待（阻塞）函数`和`线程通知（唤醒）函数`。定义于头文件`<condition_variable>`

* 等待函数

调用wait()函数的线程会被阻塞

```c++
// ①
void wait (unique_lock<mutex>& lck);
// ②
template <class Predicate>
void wait (unique_lock<mutex>& lck, Predicate pred);
```

函数①：调用该函数的线程直接被阻塞

函数②：该函数的第二个参数是一个判断条件，是一个返回只为bool类型的函数

    该参数可以传递一个有名函数的地址，也可以直接指定一个匿名函数

    表达式返回false当前线程被阻塞，表达式返回true当前线程不会被阻塞，继续向下执行


# 内存管理

* 操作系统的内存管理包括物理内存和虚拟内存管理

**物理内存管理**:包括程序装入等概念，交换技术，连续分配管理方式和非连续分配管理方式（分页，分段，段页式）

**虚拟内存管理**:包括虚拟内存概念，请求分页管理方式，页面置换算法，页面分配策略，工作集和抖动

# 死锁

**死锁**是指两个或两个以上的进程在执行过程中，由于资源竞争或由于彼此之间通信而造成的一种阻塞现象，若无外力作用，他们都无法推进下去。此时称系统处于死锁状态

* 系统资源不足
* 程序执行顺序有问题
* 资源分配不当

## 资源分级法
为每个资源分配一个唯一的等级，并且要求进程必须按照资源的等级顺序请求资源。这样，循环等待的情况就不会发生，从而预防了死锁

# C++异常处理
* throw:当问题出现时，程序会抛出一个异常，使用throw关键字来完成
* catch：在想要处理问题的地方，通过异常处理程序捕获异常
* try：try中代码块标识将被激活的特定异常，后面常跟着一个或多个catch块

# 其他
## emplace_back()
用与在容器的尾部直接构造新元素，而不需要显示地进行拷贝构造或移动操作

与push_back()不同，emplace_back()允许我们将参数直接传递给元素的构造函数，从而在容器中就地构造新元素

```c++
threads.emplace_back([&fileManager](){
    //模拟并发访问文件操作
    string content=fileManager.queryFile("test.txt");
    cout<<"Thread accessed file with content:"<<content<<endl;
});
```

&fileManager:是一个lambda表达式的捕获列表，指定了要在lambda函数中使用的外部变量。在这个例子中，捕获了fileManager变量，以便在lambda表达式中使用它

[&fileManager](){...}：这是一个lambda函数，表示线程要执行的操作。lambda函数以[]包围捕获列表，后面是函数参数列表（此处为空），然后是函数体

表示引用传递捕捉变量&fileManager

## unique_ptr
* 是C++11提供的用于防止内存泄漏的智能指针中的一种实现，**独享被管理对象指针所有权的智能指针**

* unique_ptr对象包装一个原始指针，并负责其生命周期。当该对象被销毁时，会在其析构函数中删除关联的原始指针

* unique_ptr有`->`,`*`运算符重载，因此可以像普通指针一样使用

```c++
#include <iostream>
#include <memory>

struct Task {
    int mId;
    Task(int id ) :mId(id) {
        std::cout << "Task::Constructor" << std::endl;
    }
    ~Task() {
        std::cout << "Task::Destructor" << std::endl;
    }
};

int main()
{
    // 通过原始指针创建 unique_ptr 实例
    std::unique_ptr<Task> taskPtr(new Task(23));

    //通过 unique_ptr 访问其成员
    int id = taskPtr->mId;
    std::cout << id << std::endl;

    return 0;
}
```
`unique_ptr<Task>`对象taskPtr接受原始指针作为参数。现在当main函数退出时，该对象超出作用范围，就会调用其析构函数，在unique_ptr对象taskPtr的析构函数中，会删除关联的原始指针，这样就不需要delete Task对象了

unique_ptr对象始终是关联的原始指针的唯一所有者。我们无法复制unique_ptr对象，它只能移动。由于每个unique_ptr对象都是原始指针的唯一所有者，因此在其析构函数中它直接删除关联的指针，不需要任何参考计数。

```c++
class Resource{
private:
    int level_;
    bool available_;
public:
    Resource(int level):level_(level),available_(true){}
    
    int getLevel()const{return level_;}//常量成员函数，在函数声明中使用const限定符表示该函数不会修改类的成员变量
    bool isAvailable()const{return available_;}

    void request(){
        if(!available_){
            throw std::runtime_error("Resource is not available");
        }
        available_=false;
    }

    void release(){
        available_=true;
    }

};

class Process{
private:
    std::vector<int>resourceLevels_;
    std::unordered_map<int,std::unique_ptr<Resource>>resources_;
}
```
* 独占所有权：unique_ptr提供了独占所有权的语义，即同一时间只能有一个指针拥有资源。资源的所有权是唯一的，没有其他指针可以同时拥有或访问它

* 自动内存管理

* std::unique_ptr<Resource>用于在Process类的成员变量resources_中管理Resource类的对象指针。这意味着resources_中的每个资源对象的内存管理都由响应的std::unique_ptr自动处理

* 通过使用std::unique_ptr，可以确保资源对象的生命周期与Process对象生命周期相匹配，同时避免资源泄漏和悬挂指针的问题

## make_unique
* 是C++11标准引入的一个模板函数，用于动态分配指定类型的内存，并返回一个指向分配内存的唯一指针，即`unique_ptr`

## std::thread

* thread的初始化构造函数
```c++
thread(Fn&& fn, Args&&... args); 

std::thread t1; // t1 is not a thread
std::thread t2(f1, n + 1); // pass by value
std::thread t3(f2, std::ref(n)); // pass by reference
std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
```
新产生的线程会调用fn函数，该函数的参数由args给出


# unordered_map

## 概述

* 存储KV值，可以通过key快速索引到value。

* 不会根据key大小进行排序

* unordered_map的底层是一个防冗余的哈希表

## 使用
at(key)	返回容器中存储的键key对应的值，如果key不存在，则会抛出out_of_range异常

# 异常处理

* C++的异常通过throw关键字和try,catch语句结构来实现

```c++
throw 关键字//常量，对象或变量

try{
    //可能会出现异常的代码
}
catch(异常类型1){
    //异常处理代码
}
```

只能有一个try语句块，可以有多个catch，以便匹配不同类型的异常。try抛出异常(throw)，只要类型与catch相同 ，就会被catch捕获

```c++
...
void request(){
    if(!available_){
        throw std::runtime_error("Resource is not available");
    }
    available_=false;
}
...

try{
    for(int level:resourceLevels_){
        resources_.at(level)->request();
        std::cout<<"Process requestd resource with level"<<level<<std::endl;
    }
    for(int level:resourceLevels_){
        resources_.at(level)->release();
        std::cout<<"Process released resource with level"<<level<<std::endl;
    }
    
}catch(const std::exception& e){
        std::cerr<<"Error:"<<e.what()<<std::endl;
    }
```

如果在请求资源时发生了异常，则会抛出一个`std::seception`异常。如果在try模块中任何一个循环中抛出了异常，程序将跳转到catch模块。在catch模块中，异常对象被捕获，通过e.what()获取异常的错误信息，然后将错误信息输出到标准错误流

# 进程间通信

## 套接字

### 概述
* 可以通过套接字实现本地单机上通信，也可以跨网络通信

### 属性

1. 套接字的域
它指定套接字通信中使用的网络介质，最常见的套接字域是AF_INET，它指的是Internet网络。当客户使用套接字进行跨网络的连接时，它就需要用到服务器计算机的IP地址和端口来指定一台联网机器上的某个特定服务，所以在使用socket作为通信的终点，服务器应用程序必须在开始通信之前绑定一个端口，服务器在指定的端口等待客户的连接。另一个域AF_UNIX表示UNIX文件系统，它就是文件输入/输出，而它的地址就是文件名。

2. 套接字的类型
因特网提供了两种通信机制：流（stream）和数据报（datagram），因而套接字的类型也就分为流套接字和数据报套接字。这里主要讲流套接字。

  流套接字由类型SOCK_STREAM指定，它们是在AF_INET域中通过TCP/IP连接实现，同时也是AF_UNIX中常用的套接字类型。流套接字提供的是一个有序、可靠、双向字节流的连接，因此发送的数据可以确保不会丢失、重复或乱序到达，而且它还有一定的出错后重新发送的机制。

  与流套接字相对的是由类型SOCK_DGRAM指定的数据报套接字，它不需要建立连接和维持一个连接，它们在AF_INET中通常是通过UDP/IP协议实现的。它对可以发送的数据的长度有限制，数据报作为一个单独的网络消息被传输,它可能会丢失、复制或错乱到达，UDP不是一个可靠的协议，但是它的速度比较高，因为它并一需要总是要建立和维持一个连接。

3. 套接字的协议
只要底层的传输机制允许不止一个协议来提供要求的套接字类型，我们就可以为套接字选择一个特定的协议。通常只需要使用默认值。
