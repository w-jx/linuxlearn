// File Name: lseek_file.c
// Author: wenjx
// Created Time: Sun Nov 29 20:00:36 2020

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
//利用lseek扩展文件大小
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
int main(){
    int fd = open("lseek.txt",O_RDWR);
    if (fd<0) 
        sys_err("file open error\n");
    int lens =  lseek(fd,111,SEEK_END);
    printf("file lens=%d\n",lens);
    close(fd);
    return 0 ;
}
