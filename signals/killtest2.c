// File Name: killtest.c
// Author: wenjx
// Created Time: Mon Nov 16 10:37:31 2020

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
#include <sys/types.h>
#include <signal.h>
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
int main(){

    pid_t pid;
    int killstatus=0;
    pid = fork();

    if (pid==0) {
        printf("this is the child,pid=%d,ppid=%d, process\n",getpid(),getppid());
        sleep(2);
        killstatus =  kill(getppid(),SIGFPE);
        if (killstatus ==0) {
            printf("kill status success\n");
        }
    }
    else{
        printf("this is the parent process,pid=%d, process\n",getpid());
        sleep(10);
        
    }


    return 0 ;
}
