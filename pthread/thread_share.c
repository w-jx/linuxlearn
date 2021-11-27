// File Name: thread_share.c
// Author: wenjx
// Created Time: 2020年11月20日 星期五 16时58分19秒

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
#include<pthread.h>
//验证主线程，子线程共享全局变量
int a=100;
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
void *tfn(void *arg) {
    a=200;
    printf("in thread,a=%d\n",a);
    return NULL;
}
int main(){
    printf("before create,a=%d\n",a);
    pthread_t tid;
    int ret;
    ret = pthread_create(&tid,NULL,tfn,NULL);
    if (ret!=0) {
        geterror("thread error");
    }
    sleep(1);
    printf("after create thread and change the i value ,a=%d\n",a);
    return 0; 
}
