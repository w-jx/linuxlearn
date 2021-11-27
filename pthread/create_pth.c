// File Name: create_pth.c
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
//创建线程,发现子线程没有错误也没有执行
//原因：创建子线程后，主线程return 了，子线程来不及执行就无了
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
    return 0 ;
}
