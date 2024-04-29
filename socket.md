# socket编成
https://www.cnblogs.com/helloworldcode/p/10610581.html
## 服务端
1. socket(),创建流式socket

2. bind()，指定由于通信的ip地址和端口

3. listen()，把socket设置为监听模式

4. accept()，接受客户端的连接

5. recv()/send()，接收/发送数据

6. close()，关闭socket连接，释放资源

### 套接字对象的创建
```c++
/*
_domain套接字使用的协议族信息
_type套接字的传输类型
_protocol通信协议
*/
int socket(int _domain,int _type,int _protocol) _THROW;
```

UNIX中，一切皆文件，socket也是一种"打开--读/写--关闭"模式实现的，可以将该函数类比常用的`open()`函数，服务器和客户端各自维护一个“文件”，在文件连接打开后，可以向自己文件写入内容供对方读取或者读取对方内容，通讯结束时关闭文件

* 第一个参数:关于协议组信息可选如下字段

AF_UNIX：实现本地通信

AF_INET:IPv4网络协议中采用的地址族

AF_INET6:IPv6网络协议中采用的地址族

AF_LOCAL:本地通信中采用的UNIX协议的地址族（用的少)

* 第二个参数：套接字类型

SOCKET_RAW：原始套接字(SOCKET_RAW)允许对较低层次的协议直接访问，比如IP、 ICMP协议。

SOCK_STREAM：SOCK_STREAM是数据流，一般为TCP/IP协议的编程。

SOCK_DGRAM：SOCK_DGRAM是数据报，一般为UDP协议的网络编程；

* 第三个参数第三个参数：最终采用的协议。常见的协议有IPPROTO_TCP、IPPTOTO_UDP。如果第二个参数选择了SOCK_STREAM，那么采用的协议就只能是IPPROTO_TCP；如果第二个参数选择的是SOCK_DGRAM，则采用的协议就只能是IPPTOTO_UDP。


### 向套接字分配网络地址--bind()
```c++
/*
_fd:socket描述字，也就是socket引用
myaddr:要绑定给socket的协议地址
_len:地址的长度
*/
int bind (int __fd, const struct sockaddr* myaddr, socklen_t __len)  __THROW;
```

* 第一个参数：socket文件描述符，_fd即套接字创建时返回的对象
* 第二个参数：myaddr则是填充了一些网络地址信息，包含通信所需要的相关信息，其结构体具体如下
```c++
struct sockaddr
  {
    sa_family_t sin_family;	/* Common data: address family and length.  */
    char sa_data[14];		/* Address data.  */
  };
```
在具体传参的时候，会用该结构体的变体sockaddr_in形式去初始化相关字段，该结构体具体形式如下，结构体sockaddr中的sa_data就保存着地址信息需要的IP地址和端口号，对应着结构体sockaddr_in的sin_port和sin_addr字段。

```c++
struct sockaddr_in{
    sa_family_t sin_family;		//前面介绍的地址族
    uint16_t sin_port;			//16位的TCP/UDP端口号
    struct in_addr sin_addr;	//32位的IP地址
    char sin_zero[8];			//不使用
}
```

in_addr结构定义如下
```c++
/* Internet address.  */
typedef uint32_t in_addr_t;
struct in_addr
{
	in_addr_t s_addr;
};
```

sin_zero无特殊含义，只是为了与下面介绍的sockaddr结构体一致而插入的成员，因为在给套接字分配网址时会调用bind函数，其中的参数会把sockaddr_in转换为sockaddr的形式

```c++
struct sockaddr_in serv_addr;
...
bind(serv_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr))；
```

### 进入等待连接请求状态
给套接字分配了所需的信息后，就可以调用listen()函数对来自客户端的连接请求进行监听（客户端此时要调用connect()函数进行连接）

```c++
/* Prepare to accept connections on socket FD.
   N connection requests will be queued before further requests are refused.
   Returns 0 on success, -1 for errors.  */
extern int listen (int __fd, int __n) __THROW;
```

* 第一个参数：socket文件描述符

* 第二个参数：连接请求的队列长度，如果为6，表示队列中最多同时有6个连接请求

这个函数的fd(socket套接字对象)就相当于一个门卫，对连接请求做处理，决定是否把连接请求放入到server端维护的一个队列中去。

### 受理客户端的连接请求

listen()中的fd发挥了服务器端接受请求的门卫作用，此时为了按序受理请求，给客户端作相应的回馈，连接到发请求的客户端，此时需要再次创建一个套接字

```c++
/* Await a connection on socket FD.
   When a connection arrives, open a new socket to communicate with it,
   set *ADDR (which is *ADDR_LEN bytes long) to the address of the connecting
   peer and *ADDR_LEN to the address's actual length, and return the
   new socket's descriptor, or -1 for errors.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int accept (int __fd, struct sockaddr *addr, socklen_t *addr_len);
```

* 第一个参数：socket文件描述符__fd，要注意的是这个套接字文件描述符与前面几步的套接字文件描述符不同。

* 第二个参数：保存发起连接的客户端的地址信息。

* 第三个参数： 保存该结构体的长度。

### send/write发送信息

```c++
/* Write N bytes of BUF to FD.  Return the number written, or -1.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
 ssize_t write (int __fd, const void *__buf, size_t __n) ;
```

### recv/read接受信息

```c++
/* Read NBYTES into BUF from FD.  Return the
   number read, -1 for errors or 0 for EOF.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
ssize_t read (int __fd, void *__buf, size_t __nbytes);
```

## 客户端

​服务端的socket套接字在绑定自身的IP即 及端口号后这些信息后，就开始监听端口等待客户端的连接请求，此时客户端在创建套接字后就可以按照如下步骤与server端通信，创建套接字的过程不再重复了。

### 请求连接

```c++
/* Open a connection on socket FD to peer at ADDR (which LEN bytes long).
   For connectionless socket types, just set the default address to send to
   and the only address from which to accept transmissions.
   Return 0 on success, -1 for errors.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
int connect (int socket, struct sockaddr* servaddr, socklen_t addrlen);
```

参数意义与accept函数意义一样。注意服务端接收到连接请求的时候，并不是马上调用accept()函数，而是放入到请求信息的等待队列中