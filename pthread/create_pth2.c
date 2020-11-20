// File Name: create_pth2.c
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
//在创建线程结束后，利用sleep(2)给子进程执行的时间，不至于主线程直接return
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
    printf("main:pid=%d,tid=%lu,\n",getpid(),pthread_self());
    
     int ret;
     ret =  pthread_create(&tid,NULL,tfn,NULL);//去执行函数

     if (ret!=0) 
         geterror("create error");
     sleep(2);
    return 0 ;
}
