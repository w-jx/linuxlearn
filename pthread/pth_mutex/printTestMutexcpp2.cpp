#include <iostream>
#include <thread>
#include <ctime>
#include <mutex>

using namespace std;

//改变加锁解锁的位置，解决只有大写的HELLO,WORLD的问题   锁的粒度要越细越好
std::mutex mtx;
void out()
{
    srand(time(NULL));
    while (true) {
        mtx.lock();
        printf("hello");
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        printf(",world!\n");
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        
    }

}
int main()
{
   
    std::thread t1(out);

    srand(time(NULL));
    while (true) {
        mtx.lock();
        printf("HELLO");
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        printf(",WORLD!\n");
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        
        
    }
    if (t1.joinable())
        t1.join();
    return 0;

}