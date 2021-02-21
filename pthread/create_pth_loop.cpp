#include <iostream> 
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
//2021/2/20 cpp
//循环创建线程    对应linuxlearn/pthread/create_pth5.c   
//我们可以在线程里面加延时 sleep_for,创建线程要用join，detach和不加都是错误的
using namespace std;

void fun(int idx) 
{
    cout<<"this is the "<<idx<<"th thread\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{

for(int i=0;i<5;i++) {
    std::thread t(fun,i);
    t.join();
}


}