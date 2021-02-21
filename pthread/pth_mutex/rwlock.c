// File Name: rwlock.c
// Author: wenjx
// Created Time: Sun Nov 22 19:42:20 2020

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
//读写锁测试,注意不检查返回值是为了程序逻辑清楚，实际工作要检查返回值
int counter=0;
pthread_rwlock_t rwlock;//读写锁
//三个线程不定时写同一资源，5个线程不定时读同一全局资源
void * th_write(void *arg)
{
    int t;
    int i=(int)arg;
    while(1) {

        pthread_rwlock_wrlock(&rwlock);//写方式加锁，独占
        t=counter;
        usleep(1000);
        printf("--write:%d,%lu:counter:%d,++counter=%d\n",i,pthread_self(),t,++counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(10000);

    }
}
void * th_read(void *arg)
{
    int i=(int)arg;
    while(1) {

        pthread_rwlock_rdlock(&rwlock);//读线程间，x读锁共享
        usleep(1000);
        printf("--read:%d,%lu:counter:%d\n",i,pthread_self(),counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(2000);

    }
}

int main(){
    int i;
    pthread_t tid[8];
    pthread_rwlock_init(&rwlock,NULL);

    for(i=0;i<3;i++) {
        pthread_create(&tid,NULL,th_write,(void*)i);

    }
    for(i=0;i<5;i++) {
        pthread_create(&tid,NULL,th_read,(void*)i);

    }
    for (i=0;i<8;i++) {
        pthread_join(tid[i],NULL);
    }
    pthread_rwlock_destroy(&rwlock);

    return 0 ;
}
