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
//mmap5.c创建映射区的时候改成私有权限，然后mmap的返回值强转成（int*)指针
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int var=100;
int main(){

    int *p=NULL;
    int fd=0;
    pid_t pid,pid1;

    fd = open("temp",O_RDWR|O_CREAT|O_TRUNC,0644);
    ftruncate(fd,4);
    int len = lseek(fd,0,SEEK_END);//获得文件大小
    p = (int*)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);//在MAP_SHARED时候能够共享
    printf("global *p=%d\n",*p);

    if (p==MAP_FAILED) {
        geterror("map error");
        exit(1);
    }
    close(fd);

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
        printf("pid1=%d\n",pid1);
        int s =  munmap(p,len);
        if (s==-1) {
            geterror("munmap error");
            exit(1);

        }
    }

    return 0 ;
}
