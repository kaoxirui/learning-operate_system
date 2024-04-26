#ifndef _DEADLOCK_H
#define _DEADLOCK_H
class Resource{
private:
    int level_;
    bool available_;
public:
    Resource(int level):level_(level),available_(true){}
    
    int getLevel()const{return level_;}//常量成员函数，在函数声明中使用const限定符表示该函数不会修改类的成员变量
    bool isAvailable()const{return available_;}

    

};
#endif