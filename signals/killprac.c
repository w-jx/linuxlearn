// File Name: killprac.c
// Author: wenjx
// Created Time: Mon Nov 16 18:02:06 2020

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
//循环创建5个子进程，父进程用kill 终止任一子进程
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
int main(){
    int i=0;
    pid_t pid;
    for(;i<5;i++) {
        pid=fork();
        if (pid==0){
            sleep(1);
            break;
        }
    }
    if (i!=5) {
        printf("child,pid=%d,getpid()=%d\n",pid,getpid());
    }
    if (i==5) {
        sleep(5);
        printf("pid=%d\n",pid);
        if (pid==getpid()) {
            printf("killed yourself\n");

        }
        else 
            printf("killed kids\n");
        int status = kill(pid,SIGKILL);
        if (status==0) {

            printf("success\n");
        }
        else {
            printf("failed\n");
        }
    }
    return 0 ;
}
