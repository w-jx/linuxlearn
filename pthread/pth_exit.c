// File Name: pth_exit.c
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
//想要exit(0)结束，然后只输出1，2，4，5几个线程的结果
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
void * tfn (void * arg)
{
    int i=(int)arg;
    if (i==2) {
        //exit(0);//效果不好，整个进程都退出了
        return NULL;
    }
    printf("thread %d:pid=%d,tid=%lu,\n",i+1,getpid(),pthread_self());
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

    }
    sleep(1);


}
