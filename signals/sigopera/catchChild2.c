// File Name: catchChild.c
// Author: wenjx
// Created Time: Tue Nov 17 20:42:00 2020

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
#include <signal.h>
//解决子进程僵尸进程的方法,循环回收
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
void catch_Child(int sigNum)
{
    pid_t wpid;
    int status=0;
    while(( wpid = wait(&status))!=-1) {
        if (WIFEXITED(status)) {
            printf("-------------seesee-------:catch child：%d,retvalue=%d,\n",wpid,WEXITSTATUS(status));
        }
    }


}
int main(){
    pid_t pid;
    int i=0;


    for(;i<5;i++) {
        pid = fork();
        if (pid==0)
            break;
    }
    if (5==i) {
        struct sigaction act,oldact;
        act.sa_handler=catch_Child;
        sigemptyset(&(act.sa_mask));
        act.sa_flags=0;
        //sigaction(SIGCHLD,&act,&oldact);
        sigaction(SIGCHLD,&act,NULL);
        printf("parent process,pid=%d\n",getpid());
        while(1);
    }
    else {
        printf("child process,pid=%d\n",getpid());
        return i;

    }
    return 0 ;
}
