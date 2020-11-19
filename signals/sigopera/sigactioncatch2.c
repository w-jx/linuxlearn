// File Name: sigcatch.c
// Author: wenjx
// Created Time: Tue Nov 17 19:41:16 2020

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
//屏蔽二号信号时，其他信号依然能被处理
//可以设置屏蔽其他信号
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
void sig_catch(int signum)//回调函数，内核调用
{
    printf("catch you,%d\n",signum);
    sleep(10);
}
int main(){
    struct sigaction act,oldact;
    //结构体的赋值
    act.sa_handler=sig_catch;
    sigemptyset(&(act.sa_mask));//只在捕捉函数时有效
    act.sa_flags =0;
    
    sigaddset(&act.sa_mask,SIGQUIT);//设置屏蔽
    int ret=0;
    while(1) {
        ret  = sigaction(SIGINT,&act,&oldact);//注册信号捕捉函数
        if (ret==-1) 
            sys_err("action err");

    }

    return 0 ;
}
