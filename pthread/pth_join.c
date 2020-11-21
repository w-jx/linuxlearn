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
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
struct thrd {
    int var;
    char str[256];
};
void * tfn(void * arg) {
    struct thrd *tval=malloc(sizeof(struct thrd));
    tval->var=100;
    strcpy(tval->str,"hello,thread");

    return (void*)tval;

}
int main(){
    pthread_t tid;
    struct thrd *retval;
    int ret = pthread_create(&tid,NULL,tfn,NULL);
    if (ret!=0) 
        sys_err("pth_cre error");
    ret = pthread_join(tid,(void**)&retval);
    if (ret!=0) 
        sys_err("join error");

    printf("child thread with var=%d,str=%s\n",retval->var,retval->str);

    free(retval);
    pthread_exit(NULL);

    return 0 ;
}
