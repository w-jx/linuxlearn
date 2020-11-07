// File Name: tinycp.c
// Author: wenjx
// Created Time: Sat Nov  7 17:32:31 2020

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
//实现简易的cp功能，拷贝文件
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
int main(){
    char buf[1024];
    int fd1 = open("1.txt",O_RDONLY);
    if (fd1==-1) {
        sys_err("open 1.txt error");
        exit(1);

    }
    int fd2 = open("5.txt",O_RDWR|O_CREAT|O_TRUNC); 
    if (fd2==-1) {
        sys_err("open 5.txt error");
        exit(1);
    }

    int n=0;

    while  ( (n=read(fd1,buf,1024))!=0) {
        //   if (n<0) {
        //     sys_err("read error");
        //   break;
        // }
        write(fd2,buf,n);


    close(fd1);
    close(fd2);

    return 0 ;
}
