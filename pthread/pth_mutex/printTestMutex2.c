// File Name: printTest.c
// Author: wenjx
// Created Time: Sun Nov 22 07:22:42 2020

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
#include<sys/stat.h>
#include <pthread.h>
//修改睡眠时间，仍然全部打印大写
pthread_mutex_t  mutex;//全局锁
void * tfn(void *arg) {
    srand(time(NULL));
    while (2) {
        pthread_mutex_lock(&mutex);
        printf("hello");
        sleep(rand()%2);
        printf(",world!\n");
        sleep(rand()%2);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;

}
int main(){
    pthread_t tid;
    int ret;
    ret = pthread_mutex_init(&mutex,NULL);//初始化互斥锁
    if (ret!=0) {
        fprintf(stderr,"mutex init error=%s\n",strerror(ret));
        exit(2);
    }

    ret =pthread_create(&tid,NULL,tfn,NULL);
    srand(time(NULL));
    if (ret!=0) {
        fprintf(stderr,"pthc_cre error=%s\n",strerror(ret));
        exit(2);
    }
    while (2) {
        pthread_mutex_lock(&mutex);
        printf("HELLO");
        sleep(rand()%2);
        printf(",WORLD!\n");
        sleep(rand()%2);
        pthread_mutex_unlock(&mutex);

    }
    pthread_join(tid,NULL);
    pthread_mutex_destroy(&mutex);//销毁互斥锁
    return 0 ;
}
