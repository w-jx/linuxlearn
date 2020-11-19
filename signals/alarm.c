// File Name: alarm.c
// Author: wenjx
// Created Time: Mon Nov 16 19:28:13 2020

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

void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
int main(){
    int i=0;
    alarm(1);
    for(;;i++)
        printf("i=%d\n",i);

    return 0 ;
}

