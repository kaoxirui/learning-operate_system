#include"filesystem.h"
#include<vector>
#include<thread>
int main(){
    FileManager fileManager;
    //创建文件
    fileManager.createFile("test.txt","Hello world");
    //并发控制示例，使用多个进程访问文件
    vector<thread>threads;
    for(int i=0;i<6;++i){
        threads.emplace_back([&fileManager](){
            //模拟并发访问文件操作
            string content=fileManager.queryFile("test.txt");
            cout<<"Thread accessed file with content:"<<content<<endl;
        });
    }
    for(auto& thread:threads){
        thread.join();
    }

    fileManager.deleteFile("test.txt");
    return 0;
}
