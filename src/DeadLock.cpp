#include"deadlock.h"
int main(){
    std::vector<int>resourceLevels={1,2,3};
    Process process(resourceLevels);
    process.execute();
    return 0;
}