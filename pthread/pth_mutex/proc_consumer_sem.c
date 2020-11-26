// File Name: proc_consumer_sem.c
// Author: wenjx
// Created Time: 2020年11月26日 星期四 13时06分07秒

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
#include <semaphore.h>
sem_t proc,consu;
int arr[5];
void * produce(void * arg) 
{
    int i=0;
    srand(time(NULL));
    while(1)  {

        sem_wait(&proc);
        arr[i]=rand()%100+1;
        printf("---produce:arr=%d\n",arr[i]);
        sem_post(&consu);
        sleep(rand()%3);
        i=(i+1)%5;

    }
    return NULL;

}

void* consume(void * arg) {
    int i=0;
    srand(time(NULL));
    while(1)  {

        sem_wait(&consu);
        printf("-----------------------consumer:arr=%d\n",arr[i]);
        arr[i]=0;
        sem_post(&proc);
        sleep(rand()%3);
        i=(i+1)%5;

    }
    return NULL;
}
void sys_err(char * s) {
printf("error:%s\n",s);
exit(1);
}
int main(){
    pthread_t tid,cid;
    int ret=0;

    ret = sem_init(&proc,0,5);
    if(ret!=0) 
        sys_err("init error");
    ret = sem_init(&consu,0,0);
    if(ret!=0) 
        sys_err("init error");


    ret = pthread_create(&tid,NULL,produce,NULL);
    if(ret!=0) 
        sys_err("create tid error");
    ret=pthread_create(&cid,NULL,consume,NULL);
    if(ret!=0) 
        sys_err("create cid error");

    pthread_join(&tid,NULL);
    pthread_join(&cid,NULL);
    sem_destroy(&proc);
    sem_destroy(&consu);

    return 0 ;
}
