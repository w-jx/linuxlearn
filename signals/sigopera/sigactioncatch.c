// File Name: .c
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
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
void sig_catch(int signum)//回调函数，内核调用
{
    printf("catch you,%d\n",signum);
}
int main(){
    struct sigaction act,oldact;
    //结构体的赋值
    act.sa_handler=sig_catch;
    sigemptyset(&(act.sa_mask));//只在捕捉函数时有效
    act.sa_flags =0;

    int ret=0;
    while(1) {
        ret  = sigaction(SIGINT,&act,&oldact);//注册信号捕捉函数
        if (ret==-1) 
            sys_err("action err");

    }

    return 0 ;
}
