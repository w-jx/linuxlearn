// File Name: try_mux.c
// Author: wenjx
// Created Time: Sun Nov 22 16:47:41 2020

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
//尝试写第一种死锁，观察现象
pthread_mutex_t mutex;
int a=100;
void * tfn(void * arg) 
{

    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    a+=10;
    printf("a=%d\n",a);
    sleep(1);

}
int main(){
    pthread_t tid;

    int ret;


    ret =pthread_create(&tid,NULL,tfn,NULL);


    pthread_join(tid,NULL);
    pthread_exit(NULL);

    return 0 ;
}
