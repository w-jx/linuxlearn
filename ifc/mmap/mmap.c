// File Name: mmmp.c
// Author: wenjx
// Created Time: 2020年11月02日 星期一 21时17分47秒

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
//mmap测试:
void geterror(char *s){
     perror(s);
     exit(-1) ;
}
int main(){
    char *p =NULL;
    int fd;

    fd =open("testmap",O_RDWR|O_CREAT|O_TRUNC,0644);
    if (fd==-1) {
        geterror("open error");
    }
#if 0
    //扩展文件大小和下面ftruncate(fd,10);
    lseek(fd,10,SEEK_END);
    write(fd,"\0",1);
    //获取文件大小
   int  lseek(fd,0,SEEK_END);
#endif

   ftruncate(fd,10);//扩展文件大小
   int len =lseek(fd,0,SEEK_END);
   p = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

   if (p ==MAP_FAILED) {

    geterror("map error");

   }
   //使用p对文件读写操作
    strcpy(p,"hello,mmap");
    printf("----%s\n",p);

    int ret = munmap(p,len);
    if (ret==-1) {

        geterror("munmap error");
    }

    return 0 ;
}
