// File Name: fifo1.c
// Author: wenjx
// Created Time: 2020年10月31日 星期六 21时14分22秒

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
//创建管道
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int fd;

int main(){

    char buf[4096];
    fd = open("myfifo",O_WRONLY);
    if (fd<0) {

        geterror("open myfifoerror");

    }
    int i=0;
    while (1) {
        sprintf(buf,"----hhhh----hhh----:%d\n",i);
        write(fd,buf,strlen(buf));
        usleep(10000);//usleep ms
        i++;

    }

    return 0 ;
}
