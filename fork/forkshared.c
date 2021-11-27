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
//结论：全局变量i=100，然后在子进程我们更改i=200，在父进程延时5秒确保即便父进程先执行也不会打印i的值
//结果发现i仍然是 100,也就是读的时候父子是共享的，当写的时候，就会复制一份新的
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
        printf("sleep for 5 seconds to make sure the i value has been changed\n");
        sleep(5);
        printf("after sleep,in father,i=%d\n",i);

    }
    return 0 ;
}
