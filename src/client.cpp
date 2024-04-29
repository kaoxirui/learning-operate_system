#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

const char* SOCKET_PATH="/tmp/my_socket";

int main(){
    int sock=0;
    struct sockaddr_un serv_addr;
    char* hello="Hello from client";
    //创建unix域套接字
    if((sock=socket(AF_UNIX,SOCK_STREAM,0))<0){
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    //准备服务器地址结构
    serv_addr.sun_family=AF_UNIX;
    strcpy(serv_addr.sun_path,SOCKET_PATH);
    //连接到服务器
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        perror("connecton failed");
        exit(EXIT_FAILURE);
    }
    send(sock,hello,strlen(hello),0);
    std::cout<<"sent to client:"<<hello<<std::endl;
    close(sock);
    return 0;
}