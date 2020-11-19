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
//问题解决：例如说父进程注册信号前，子进程已经执行，就无法回收了，所以需要处理
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
void catch_Child(int sigNum)
{
    pid_t wpid;
    int status=0;
    while(( wpid = wait(&status))!=-1) {//循环回收，防止僵尸进程出现

        if (WIFEXITED(status)) {

            printf("----------------------:catch child：%d,retvalue=%d,\n",wpid,WEXITSTATUS(status));
        }


    }


}
int main(){
    pid_t pid;
    int i=0;
    //阻塞SIGCHLD信号
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGCHLD);
    sigprocmask(SIG_BLOCK,&set,NULL);
    for(;i<15;i++) {
        pid = fork();
        if (pid==0)
            break;
    }
    if (15==i) {
        struct sigaction act,oldact;
        act.sa_handler=catch_Child;
        sigemptyset(&(act.sa_mask));
        act.sa_flags=0;
        //sigaction(SIGCHLD,&act,&oldact);

        sigaction(SIGCHLD,&act,NULL);
        sigprocmask(SIG_UNBLOCK,&set,NULL);
        //解除阻塞
        printf("parent process,pid=%d\n",getpid());
        //while(1);
        //sleep(5);
    }
    else {
        //sleep(1);//睡可以解决，但是会造成卡顿
        printf("child process,pid=%d\n",getpid());
        return i;

    }
    return 0;
}
