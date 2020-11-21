// File Name: pth_recy.c
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
//pthread_join回收多个子进程
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
struct thrd {

    int var;
    char str[256];
};
void * tfn(void * arg) {
    printf("this is %lu thread\n",(int)arg);
    struct thrd *tval=malloc(sizeof(struct thrd));
    tval->var=100;
    strcpy(tval->str,"hello,thread");

    return (void*)tval;

}
int main(){
    pthread_t tid[5];
    struct thrd *retval;
    int ret;
    for(int i=0;i<5;i++) {
        ret = pthread_create(&tid[i],NULL,tfn,(void*)i);
        if (ret!=0) 
            sys_err("pth_cre error");
        ret = pthread_join(tid[i],(void**)&retval);
        if (ret!=0) 
            sys_err("join error");
        printf("pthread %d is recyed\n",i);
        printf("child thread with var=%d,str=%s\n",retval->var,retval->str);
    }

    pthread_exit(NULL);

    return 0 ;
}
