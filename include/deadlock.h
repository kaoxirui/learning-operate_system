#ifndef _DEADLOCK_H
#define _DEADLOCK_H
#include<iostream>
#include<vector>
#include<unordered_map>
#include<stdexcept>
#include<memory>
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

public:
    Process(const std::vector<int>& resourceLevels):resourceLevels_(resourceLevels){}

    void execute(){
        for(int level:resourceLevels_){
            resources_.emplace(level,std::make_unique<Resource>(level));
        }
        //调用make_unique<Resoures>(level)创建了一个新的Resources对象，
        //并使用Unique_ptr进行管理，然后该指针插入到resources_中，以便在后续操作中使用该对象资源
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
    }
};

#endif