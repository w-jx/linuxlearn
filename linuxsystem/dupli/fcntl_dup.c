// File Name: fcntl_dup.c
// Author: wenjx
// Created Time: 2021年01月10日 星期日 12时06分35秒

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

void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(int argc,char **argv){
    int fd=open(argv[1],O_RDWR|O_APPEND);
    int newfd = fcntl(fd,F_DUPFD,fd);
    char buf[1024]="hello,world\n";

    write(newfd,buf,strlen(buf));//体会 strlen 和sizeof的区别，包含\0
    return 0 ;
}
