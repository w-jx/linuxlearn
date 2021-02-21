#if 0   在vs2019 已经通过
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <ctime>
#include <mutex>
#include <condition_variable>
#include <semaphore>   //c++20才开始支持 ,vscode 不支持
#include <array>
using namespace std;
std::counting_semaphore proc(5);
std::counting_semaphore consu(0);

array<int, 5> arr{ 0,0,0,0,0 };

void producer()
{
	size_t i = 0;
	srand(time(nullptr));
	while (true) {
		proc.acquire();//相当于sem_wait() --操作
		arr[i] = rand() % 100 + 1;
		printf("---produce:arr=%d\n", arr[i]);
		consu.release();//sem_post() ++操作
		std::this_thread::sleep_for(std::chrono::seconds(1));
		i = (i + 1) % 5;
	}
}

void consumer()
{
	size_t i = 0;
	srand(time(nullptr));

	while (true) {
		consu.acquire();//-- 为负 就会阻塞在这里
		printf("-----------------------consumer:arr=%d\n", arr[i]);
		arr[i] = 0;
		proc.release();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		i = (i + 1) % 5;
	}

}

int main()
{


	std::thread t_proc(producer);
	std::thread t_consu(consumer);

	if (t_proc.joinable())
		t_proc.join();
	if (t_consu.joinable())
		t_consu.join();
}


#endif