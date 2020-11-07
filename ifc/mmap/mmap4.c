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
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int var=100;
int main(){

    char *p=NULL;
    int fd=0;
    pid_t pid,pid1;

    fd = open("testmap",O_RDWR|O_APPEND);
    int len = lseek(fd,0,SEEK_END);//获得文件大小

    //p = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    p = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);//改成MAP_PRIVATE

    if (p==MAP_FAILED) {
        geterror("map error");
        exit(1);

    }
    close(fd);

    pid = fork();

    if (pid==0) {
        strcpy(p+len,"heeeedhsjdh");        
        var+=100;
        printf("child,pid=%d,var=%d,*p=%d,\n",getpid(),var,*p);

    }
    else {
        sleep(1);
        printf("parent,pid=%d,var=%d,*p=%d\n",getpid(),var,*p);
        printf("p=%s\n",p);
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
