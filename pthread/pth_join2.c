// File Name: pth_join.c
// Author: wenjx
// Created Time: Sat Nov 21 07:39:05 2020

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
//错误的版本，不要返回局部变量的地址
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
void * tfn(void * arg) {
    int a=10;
    return (void*)&a;
}
int main(){
    pthread_t tid;
    int *val;
    int ret = pthread_create(&tid,NULL,tfn,NULL);
    if (ret!=0) 
        sys_err("pth_cre error");
    ret = pthread_join(tid,(void**)&val);
    if (ret!=0) 
        sys_err("join error");

    if (val==NULL) {//尝试返回局部变量地址，这个val是空，自然解引用错误
        printf("val is null pointer\n");
    }
    else {
        printf("val is not null pointer\n");
        printf("child thread with val=%d\n",*val);

    }
    printf("child thread with val=%d\n",*val);

    pthread_exit(NULL);

    return 0 ;
}
