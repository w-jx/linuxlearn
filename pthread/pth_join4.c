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
//在pth_join.c的基础上，利用pthread_create传参
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
struct thrd {

    int var;
    char str[256];
};
void * tfn(void * arg) {
    struct thrd *tval=(struct thrd*) arg;//不初始化，直接传参
    tval->var=100;
    strcpy(tval->str,"hello,thread");

    return (void*)tval;
}
int main(){
    pthread_t tid;
    struct thrd arg;
    struct thrd *retval;
    int ret = pthread_create(&tid,NULL,tfn,(void*)&arg);
    if (ret!=0) 
        sys_err("pth_cre error");
    ret = pthread_join(tid,(void**)&retval);
    if (ret!=0) 
        sys_err("join error");

    printf("child thread with var=%d,str=%s\n",retval->var,retval->str);


    pthread_exit(NULL);

    return 0 ;
}
