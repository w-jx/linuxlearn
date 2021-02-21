#include <iostream>
#include <thread>
#include <ctime>
#include <mutex>

using namespace std;

//尝试加一把锁 ，发现这样只有大写的HELLO,WORLD！
std::mutex mtx;
void out()
{
    srand(time(NULL));
    while (true) {
        mtx.lock();
        printf("hello");
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        printf(",world!\n");
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        mtx.unlock();
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
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        mtx.unlock();
        
    }
    if (t1.joinable())
        t1.join();
    return 0;

}