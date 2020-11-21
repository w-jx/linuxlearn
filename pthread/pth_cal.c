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
//测试pthread_cancel
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
void * tfn (void * arg)
{
    //printf("thread:pid=%d,tid=%lu,\n",getpid(),pthread_self());//printf能进内核
    //所以cancels成功，如果我们 b注释这句话，再来尝试下

return NULL;

}
int main(){
    pthread_t tid;
    printf("main:pid=%d,tid=%lu,\n",getpid(),pthread_self());
    
     int ret;
     ret =  pthread_create(&tid,NULL,tfn,NULL);//去执行函数
     if (ret!=0) 
         geterror("create error");
    
     ret = pthread_cancel(tid);
     if (ret!=0) 
         geterror("cancel error");
     else 
         printf("canceled success\n");
    pthread_exit(NULL);
    return 0 ;
}
