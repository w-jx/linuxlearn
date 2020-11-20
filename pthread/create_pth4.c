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
//教程里的强转
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
void * tfn (void * arg)
{
    printf("thread %d:pid=%d,tid=%lu,\n",(int)arg,getpid(),pthread_self());
    return NULL;

}
int main(){
    pthread_t tid;
    printf("main:pid=%d,tid=%lu,\n",getpid(),pthread_self());

    int ret;
    for(int i=0;i<5;i++) {
        ret =  pthread_create(&tid,NULL,tfn,(void*)i);//去执行函数
        if (ret!=0) 
            geterror("create error");
      // sleep(1);这个sleep(1)放在这边还是放在下面都是可以正常输出

    }
       sleep(1);

}
