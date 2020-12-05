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
//复习重写execlp函数测试,测试结果我没有写两个ls，一样执行
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(){

    pid_t pid;

    pid =fork();

    if (pid==0) {

        execlp("ls","-l","-h",NULL);//测试错误版本
       // execlp("ls","ls","-l","-h",NULL);//正确版本
    }
    else if (pid>0) {
        sleep(1);
        printf("i am parent\n");

    }
    return 0 ;
}
