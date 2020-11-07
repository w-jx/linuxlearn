// File Name: mmap4.c
// Author: wenjx
// Created Time: Sat Nov  7 10:20:24 2020

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
#include <sys/mman.h>
//建立匿名映射区
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int var=100;
int main(){

    int *p=NULL;
    pid_t pid,pid1;
    //匿名映射 大小可以自己填写，然后文件描述符为-1
    p = (int*)mmap(NULL,40,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);//创建匿名映射
    printf("global *p=%d\n",*p);

    if (p==MAP_FAILED) {
        geterror("map error");
        exit(1);
    }

    pid = fork();

    if (pid==0) {
        var+=100;
        *p+=10;
        printf("child,pid=%d,var=%d,*p=%d,\n",getpid(),var,*p);

    }
    else {
        sleep(1);
        printf("parent,pid=%d,var=%d,*p=%d\n",getpid(),var,*p);
        pid1 = wait(NULL);
        printf("parent get child pid1=%d\n",pid1);
        int s =  munmap(p,40);
        if (s==-1) {
            geterror("munmap error");
            exit(1);

        }
    }

    return 0 ;
}
