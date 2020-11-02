// File Name: fiforw.c
// Author: wenjx
// Created Time: 2020年11月02日 星期一 14时51分33秒

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
//管道读写通信实例
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
char buffer[80];
int fd;
int main()
{
    pid_t pid = fork();
    if (pid==-1) {
        geterror("fork error");
    }
    if (pid>0) {
        char s[] ="hello,\n";
        fd = open("myfifo",O_WRONLY);
        write(fd,s,sizeof(s));
        close(fd);
    }
    else {
        fd = open("myfifo",O_RDONLY);
        read(fd,buffer,sizeof(buffer));
        printf("from main process\n");
        printf("%s",buffer);
        close(fd);
    }
    return 0 ;
}
