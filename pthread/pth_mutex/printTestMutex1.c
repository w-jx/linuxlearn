// File Name: printTest.c
// Author: wenjx
// Created Time: Sun Nov 22 07:33:42 2020

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
//几乎和教程里面一样的程序，但是只输出主线程的东西，尝试检查问题
pthread_mutex_t  mutex;//全局锁
void * tfn(void *arg) {
    srand(time(NULL));
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("hello");
        sleep(rand()%3);
        printf(",world!\n");
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;

}
int main(){
    pthread_t tid;
    int ret;
    srand(time(NULL));
    ret = pthread_mutex_init(&mutex,NULL);//初始化互斥锁
    if (ret!=0) {
        fprintf(stderr,"mutex init error=%s\n",strerror(ret));
        exit(1);
    }

    ret =pthread_create(&tid,NULL,tfn,NULL);
    if (ret!=0) {
        fprintf(stderr,"pthc_cre error=%s\n",strerror(ret));
        exit(1);
    }
    while (1) {
        ret= pthread_mutex_lock(&mutex);
        if (ret!=0) {
            fprintf(stderr,"lock error=%s\n",strerror(ret));
            exit(1);
        }
        printf("HELLO");
        sleep(rand()%3);
        printf(",WORLD!\n");
        ret= pthread_mutex_unlock(&mutex);
        sleep(2);//注意：原程序这边和子进程这边都是sleep(rand()%3);
        if (ret!=0) {
            fprintf(stderr,"lock error=%s\n",strerror(ret));
            exit(1);
        } 
    }
    pthread_join(tid,NULL);
    pthread_mutex_destroy(&mutex);//销毁互斥锁
    return 0 ;
}
