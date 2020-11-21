// File Name: pth-create_detch.c
// Author: wenjx
// Created Time: 2020年11月20日 星期五 15时20分33秒

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
//创建线程时候就是分离态
void * tfn (void * arg)
{
    printf("thread:pid=%d,tid=%lu,\n",getpid(),pthread_self());

    return NULL;

}
int main(){
    pthread_t tid;
    int ret;
    pthread_attr_t attr;//s创建线程的属性
    ret  = pthread_attr_init(&attr);//初始化线程属性
    if (ret!=0){ 
        fprintf(stderr,"attr_init errno=%s\n",strerror(ret));
        exit(1);
    }
    //设置线程属性为分离属性
    ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
        if (ret!=0){ 
            fprintf(stderr,"attr_set errno=%s\n",strerror(ret));
            exit(1);
        }

    ret =  pthread_create(&tid,&attr,tfn,NULL);//去创建线程
    ret  = pthread_attr_destroy(&attr);//销毁线程属性所占用的资源
    if (ret!=0){ 
        fprintf(stderr,"attr_destroy errno=%s\n",strerror(ret));
        exit(1);
    }
    //验证是否是分离态，一个可以利用get,一个也可以j用join回收，回收失败就是分离态
    ret =  pthread_join(tid,NULL);
    if (ret!=0){ 
        fprintf(stderr,"join errno =%s\n",strerror(ret));
        exit(1);
    }   
    printf("main:pid=%d,tid=%lu,\n",getpid(),pthread_self());

    pthread_exit(NULL);//u关闭主线程·
    return 0 ;
}
