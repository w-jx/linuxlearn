#include <iostream>
#include <thread>
#include <shared_mutex>
#include <ctime>
#include <mutex>
#include <unistd.h>
#include <condition_variable>
using namespace std;

//条件变量实现的生产者 消费者模型 
struct msg
{
    msg() = default;
    msg(int _num) : num(_num), next(nullptr) {}
    struct msg *next;
    int num;
};
struct msg *head;

std::mutex mtx; //锁
std::condition_variable has_product;

void producer()
{
    srand(time(nullptr));
    while (true)
    {
        msg *mp = new msg(rand() % 1000); //模拟生产数据
        printf("---proc,mp->num=%d\n", mp->num);
        {
            std::unique_lock<std::mutex> mylock(mtx);
            mp->next = head;
            head = mp;
        }

        has_product.notify_one(); //唤醒阻塞在条件变量的线程
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 3));
    }
}
void consumer()
{
    srand(time(nullptr));
    while (true)
    {
        {
            msg *mp=nullptr;
            //std::lock_guard<std::mutex> mylock(mtx);
            std::unique_lock<std::mutex> mylock(mtx);
            {
                if (head == nullptr)
                    has_product.wait(mylock);
                //如果阻塞，说明没有生产好
                mp=head;
                head=mp->next;
            }
              printf("====================---consumer,mp->num=%d\n",mp->num);
              delete mp;
              std::this_thread::sleep_for(std::chrono::seconds(rand()%3));
        }
    }
}
int main()
{

    std::thread t_producer(producer);
    std::thread t_consumer(consumer);

    if (t_producer.joinable())
        t_producer.join();
    if (t_consumer.joinable())
        t_consumer.join();

    return 0;
}