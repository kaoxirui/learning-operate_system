#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H
#include<mutex>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class FileManager{
private:
    mutex mtx;

public:
    FileManager(){};
    //创建文件
    bool createFile(const string& filename,const string& content){
        lock_guard<mutex>lock(mtx);//锁定互斥量，构造时使互斥量加锁，析构时使互斥量解锁。此时的作用域在函数的整个函数体内
        ofstream file(filename);
        if(file.is_open()){
            file<<content;
            file.close();
            return true;
        }
        return false;
    }
    //删除文件
    bool deleteFile(const string& filename){
        lock_guard<mutex>lock(mtx);
        return remove(filename.c_str())==0;
    }
    //修改内容
    bool modifyFile(const string& filename,const string& newContent){
        lock_guard<mutex>lock(mtx);
        ofstream file(filename);
        if(file.is_open()){
            file<<newContent;
            file.close();
            return true;
        }
        return false;
    }
    //查询文件内容
    string queryFile(const string& filename){
        lock_guard<mutex>lock(mtx);
        ifstream file(filename);
        string content((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
        return content;
    }
};
#endif