#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

const char* SOCKET_PATH="/tmp/my_socket";

int main(){
    int server_fd,new_socket;
    struct sockaddr_un address;
    int opt=1;
    int addrlen=sizeof(address);
    char buffer[1024]={0};
    ssize_t bytes;

    //创建unix域套接字
    if((server_fd=socket(AF_UNIX,SOCK_STREAM,0))==0){
        perror("socker failed");
        exit(EXIT_FAILURE);
    }
    //设置套接字为非阻塞
    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))){
        perror("SO_REUSEADDR");
        exit(EXIT_FAILURE);
    }
    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))){
    perror("SOCK_NONBLOCK");
    exit(EXIT_FAILURE);
    }
    //准备套接字地址结构
    address.sun_family=AF_UNIX;
    strncpy(address.sun_path,SOCKET_PATH,sizeof(address.sun_path)-1);

    //绑定套接字到地址
    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    //监听套接字
    if(listen(server_fd,3)<0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    std::cout<<"Server listening on "<<SOCKET_PATH<<std::endl;
    //接受客户端发送的消息
    if((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&address))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    //读取客户端发送的消息
    bytes=recv(new_socket,buffer,1024,0);
    if(bytes<0){
        perror("recv");
    }else{
        buffer[bytes]='\0';
        std::cout<<"Received from client: "<<buffer<<std::endl;
    }
    //关闭套接字
    close(new_socket);
    close(server_fd);
    unlink(SOCKET_PATH);
}