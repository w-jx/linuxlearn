#include <iostream> 
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
//2021/2/20 cpp
//循环创建线程    对应linuxlearn/pthread/create_pth5.c   
//所以这个位置放在 fun里面 还有创建线程都可以
//不加也不会出错，顺序没有错误
using namespace std;

void fun(int idx) 
{
    cout<<"this is the "<<idx<<"th thread\n";
    //std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{

for(int i=0;i<100;i++) {
    std::thread t(fun,i);
    //std::this_thread::sleep_for(std::chrono::seconds(1));//阻塞主线程运行
    t.join();
}


}