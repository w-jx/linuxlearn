#include <iostream>
#include <thread>
#include <ctime>

using namespace std;

//输出测试cpp 2020.02.10 可以发现没加锁，输出不整齐
//有这样的现象    helloHELLO,world!
void out()
{
    srand(time(NULL));
    while (true) {
        printf("hello");
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        printf(",world!\n");
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
    }

}
int main()
{

    std::thread t1(out);

    srand(time(NULL));
    while (true) {
        printf("HELLO");
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        printf(",WORLD!\n");
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
    }
    if (t1.joinable())
        t1.join();
    return 0;

}