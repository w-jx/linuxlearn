// File Name: mmap6.c
// Author: wenjx
// Created Time: Sat Nov  7 15:13:09 2020

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
//无血缘关系的进程间通信,这个进程是读进程
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
struct Student
{
    int id;
    char name[256];
    int age;
};
int main(){

    printf("经过编译的\n");
    struct Student stu={1,"dddd",13};
    struct Student *p;
    
    // printf("sizeof(stu)=%d\n",sizeof(stu));264,加一起
    int fd;

    fd =open("testmap",O_RDWR|O_TRUNC,0644);
    if (fd==-1) {
        geterror("open file error");
        exit(1);
    }
    p = mmap(NULL,sizeof(stu),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if (p==MAP_FAILED) {
        geterror("map error");
        exit(1);
    
    }
    p->id=0;
    while (1) {
        printf("id=%d,name=%s,age=%d\n",p->id,p->name,p->age);
        if (p->id>10000) break;
        usleep(1000);
    }
    int st =munmap(p,sizeof(stu));
    if (st==-1) {
        geterror("munmap error");
        exit(1);

    }


    return 0 ;
}
