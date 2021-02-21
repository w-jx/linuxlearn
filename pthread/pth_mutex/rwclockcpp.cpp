#include <iostream>
#include <thread>
#include <shared_mutex>
#include <ctime>
#include <mutex>
#include <unistd.h>
using namespace std;

//利用shared_mutex 实现读写锁 c++17支持

std::shared_mutex mtx;

int counter=0;//全局变量

void th_write(int idx)
{
    int t=0;
    while (true) {
        mtx.lock();//独占锁？
        t=counter;
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        printf("--write:%d,%lu:counter:%d,++counter=%d\n",idx,std::this_thread::get_id(),t,++counter);
        mtx.unlock();
         std::this_thread::sleep_for(std::chrono::microseconds(10000));
    }

}

void th_read(int idx)
{
   
    while (true) {

        mtx.lock_shared();//独占锁？
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        printf("--read:%d,%lu:counter:%d\n",idx,std::this_thread::get_id(),counter);
        mtx.unlock_shared();
        std::this_thread::sleep_for(std::chrono::microseconds(2000));
    }
}

int main()
{

std::thread t[8];//8个线程

for(int i=0;i<3;i++) {
    t[i]=std::thread(th_write,i);//3个写
}
for(int i=3;i<8;i++) {
      t[i]=std::thread(th_read,i);//5个读
}
for(int i=0;i<8;i++) {
    if (t[i].joinable())
        t[i].join();
}

return 0;

}