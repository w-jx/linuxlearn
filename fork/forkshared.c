// File Name: forkshared.c
// Author: wenjx
// Created Time: 2021年03月03日 星期三 10时28分51秒

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
// 测试父子进程全局变量
int i  =100;
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(int argc,char **argv){
    pid_t pid;

    pid = fork() ;
    if (pid==0) {
        printf("in child,i=%d\n",i);
        i=200;
        printf("after child i=200,i=%d\n",i);
    }
    else if(pid >0) {
        printf("in father,i=%d\n",i);
        sleep(5);

        printf("after sleep,in father,i=%d\n",i);

    }
    return 0 ;
}
