// File Name: proc_consumer.c
// Author: wenjx
// Created Time: Sun Nov 22 20:41:42 2020

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
//生产者消费者模型代码
struct msg {

    struct  msg* next;
    int num;

};
struct msg *head;
//静态初始化
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;
void * producer(void*arg) {
    while(1) {
        struct msg *mp=malloc(sizeof(struct msg));
        mp->num=rand()%1000;//模拟生产数据
        printf("---proc,mp->num=%d\n",mp->num);
        pthread_mutex_lock(&mutex);//加锁
        mp->next=head;//写公共区域操作
        head=mp;
        pthread_mutex_unlock(&mutex);//解锁
        pthread_cond_signal(&has_product);//唤醒阻塞再条件变量 has_data上的变量
        sleep(rand()%3);}
    return NULL;
}
void* consumer(void* arg) {

    while(1) {
        struct msg *mp;
        pthread_mutex_lock(&mutex);//加锁
        if (head==NULL) //空的时候才判断不为空直接消费即可
            pthread_cond_wait(&has_product,&mutex);//阻塞等待条件变量,解锁
        //当pthread_cond_waitw返回时，会重新加锁
        mp=head;
        head=mp->next;
        pthread_mutex_unlock(&mutex);
        printf("====================---consumer,mp->num=%d\n",mp->num);
        free(mp);
        sleep(rand()%3);}
    return NULL;
}
int main(){
    pthread_t tid[2];
    int ret=-1;
    srand(time(NULL));
    ret = pthread_create(&tid[0],NULL,producer,NULL);
    if (ret!=0) {
        fprintf(stderr,"create err:&s\n",strerror(ret));
    }
    ret=pthread_create(&tid[1],NULL,consumer,NULL);
    if (ret!=0) {
        fprintf(stderr,"create err:&s\n",strerror(ret));
    }

    pthread_join(&tid[0],NULL);
    pthread_join(&tid[1],NULL);
    return 0 ;
}
