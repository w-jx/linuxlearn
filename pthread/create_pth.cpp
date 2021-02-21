#include <iostream> 
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
//2021/2/20 cpp
//创建线程    对应linuxlearn/pthread/create_pth.c   

using namespace std;

void fun() 
{
    cout<<"hello\n";   
}

void funwithparam(int a)//带参数的线程函数
{
    cout<<"a="<<a<<",id="<<pthread_self()<<endl;
}
int main()
{

std::thread t1(fun);
t1.join();

std::thread t2(funwithparam,11);

sleep(1);
std::thread::id t2_id = t2.get_id();

cout<<"t2_id="<<t2_id<<endl;//对应的是pthread_self(),结果相同

//get_id()  未被结合或者分离的非空任务线程会返回非0的整数作为子线程的标识符
//如果t2.join()后 结果为thread::id of a non-executing thread
t2.join();
cout<<"thread over\n";
return 0;

}