// File Name: pth_exit3.c
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
//用pthread_exit(NULL)退出当前线程，不管是在函数中使用还是直接使用，都是正常的
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
void func(void) {
    pthread_exit(NULL);
    return ;
}
void * tfn (void * arg)
{
    int i=(int)arg;
    if (i==2) {
        //exit(0);//效果不好，整个进程都退出了
        // return NULL;
        //func();//这样可以，也可以直接把pthread_exit（NULL）放在这边
    pthread_exit(NULL);
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
