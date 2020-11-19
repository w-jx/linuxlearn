// File Name: sigtest.c
// Author: wenjx
// Created Time: Tue Nov 17 19:00:07 2020

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
void print_set(sigset_t* set) 
{
    for(int i=1;i<32;i++) {//查看二进制位
        if( sigismember( set,i)) 
            putchar('1');
        else
            putchar('0');

    }
    printf("\n");

}
int main(){

    sigset_t set,oldset,pedset;
    int ret=0;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGKILL);//验证SIGKILL无法被屏蔽
    ret = sigprocmask(SIG_BLOCK,&set,&oldset);

    if (ret==-1) {

        sys_err("mask error\n");
    }
    while(1){
        ret = sigpending(&pedset); 
        if (ret==-1) {

            sys_err("pedding error\n");
        }
        print_set(&pedset);
        sleep(1);
    }

    return 0 ;
}
