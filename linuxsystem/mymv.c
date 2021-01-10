// File Name: mymv.c
// Author: wenjx
// Created Time: 2021年01月07日 星期四 08时59分52秒

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
//使用link,unlink一起实现 mv命令的功能
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(int argc,char **argv){
    int ret =link(argv[1],argv[2]);
    if (ret!=0)
        geterror("link error\n");
    ret =unlink(argv[1]);
    if (ret!=0)
        geterror("unlink error\n");

    return 0 ;
}
