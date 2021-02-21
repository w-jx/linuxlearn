#include <iostream>
#include <thread>
#include <ctime>
#include <mutex>

using namespace std;

//手册上说一般不用mutex.lock()和unlock(),而是用std::unique_lock 与 std::lock_guard 管理排他性锁定。
//在锁离开作用域时自动释放 ,锁不会离开作用域？
//发现用lock_guard 不能正常执行
//相当于在一开始mtx.lock() 然后再最后mtx.unlock();就是printTestMutexcpp.cpp的情况
std::mutex mtx;
void out()
{
    
    srand(time(NULL));
    
    while (true) {
        std::lock_guard<std::mutex> qlock(mtx); 
        printf("-hello");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%30));
        printf(",world!\n");
        
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%30));
        
    }

}
int main()
{
   
    std::thread t1(out);
  

    srand(time(NULL));
    while (true) {
        std::lock_guard<std::mutex> qlock(mtx); 
        printf("HELLO");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%30));
        printf(",WORLD!\n");
       
        //std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
    }
    if (t1.joinable())
        t1.join();
    return 0;

}