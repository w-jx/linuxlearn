// File Name: pth-detch.c
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
//pthread_detach测试
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
void * tfn (void * arg)
{
    printf("thread:pid=%d,tid=%lu,\n",getpid(),pthread_self());

    return NULL;

}
int main(){
    pthread_t tid;

    int ret;
    ret =  pthread_create(&tid,NULL,tfn,NULL);//去执行函数
    if (ret!=0) 
        geterror("create error");

    ret=pthread_detach(tid);//设置线程分离
    if (ret!=0) 
        geterror("detach error");
    sleep(1);
    ret =  pthread_join(tid,NULL);
    printf("first,join ret = %d,errno=%d\n",ret,errno);
    if (ret!=0) {
    printf("second,join ret = %d,errno=%d\n",ret,errno);
        printf("join errno=%s\n",strerror(errno));
        fprintf(stderr,"join ret errno=%s\n",strerror(ret));
        geterror("join errno");
    }

    printf("main:pid=%d,tid=%lu,\n",getpid(),pthread_self());

    pthread_exit(NULL);//u关闭主线程·
    return 0 ;
}
