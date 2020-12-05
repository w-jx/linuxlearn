// File Name: execlptest.c
// Author: wenjx
// Created Time: 2020年12月02日 星期三 21时06分09秒

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
//利用execl执行可执行程序,不执行BASH内容了
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(){

    pid_t pid;

    pid =fork();

    if (pid==0) {

        execl("./print","./print",NULL);//用execl执行可执行程序
    }
    else if (pid>0) {
        sleep(1);
        printf("i am parent\n");

    }
    return 0 ;
}
