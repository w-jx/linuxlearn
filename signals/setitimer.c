// File Name: setitimer.c
// Author: wenjx
// Created Time: Mon Nov 16 19:59:10 2020

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>
#include<math.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>

void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
int main(){
struct itimerval new_t;
struct itimerval old_t;

new_t.it_interval.tv_sec = 0;
new_t.it_interval.tv_usec = 0;
new_t.it_value.tv_sec = 1;
new_t.it_value.tv_usec = 0;

old_t.it_interval.tv_sec = 0;
old_t.it_interval.tv_usec = 0;
old_t.it_value.tv_sec = 0;
old_t.it_value.tv_usec = 0;

setitimer(ITIMER_REAL,&new_t,&old_t);

    for(int i=0;;i++) {

        printf("i=%d\n",i);

    }


    return 0 ;
}
