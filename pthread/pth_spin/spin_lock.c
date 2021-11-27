#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include <pthread.h>
#include<sys/stat.h>

pthread_spinlock_t lock;


void * PrintLow(void *arg)
{
    while (1) {
        pthread_spin_lock(&lock);
        printf("-->小写\n");
        pthread_spin_unlock(&lock);
        sleep(1);
    }

}
void *PrintUp(void *arg)
{
    while (1) {
        pthread_spin_lock(&lock);
        printf("大写\n");
        pthread_spin_unlock(&lock);
        sleep(1);
    }
}
int main()
{
    /*
PTHREAD_PROCESS_PRIVATE
自旋锁只能由与调用pthread_spin_init()的线程处于同一进程的线程操作。 (尝试在进程之间共享自旋锁会导致未定义的行为。)
PTHREAD_PROCESS_SHARED
自旋锁可以由有权访问包含该锁的内存的任何进程中的任何线程操作(即，该锁可以在多个进程之间共享的共享内存对象中)。
    */
    pthread_spin_init(&lock,PTHREAD_PROCESS_PRIVATE);
    pthread_t t_lower,t_upper;//打印大小写
    int ret = pthread_create(&t_lower,NULL,PrintLow,NULL);
    if (ret!=0) {
        perror("t_lower error\n");
        return 0;
    }
    ret  = pthread_create(&t_upper,NULL,PrintUp,NULL);
    if (ret!=0) {
        perror("t_upper error\n");
        return 0;
    }
    pthread_join(t_lower,NULL);
    pthread_join(t_upper,NULL);
    return 0;
}