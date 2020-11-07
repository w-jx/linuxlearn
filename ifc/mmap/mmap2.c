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
//现在testamap大小非0，然后
//测试下文件打开O_RDWR，然后mmap的port参数PORT_WRITE会不会出错
//2.测试创建完mmap映射区即关闭文件描述符，不会出错
//3.测试文件偏移量1000，4096的时候的情况，为了测试偏移量4096的情况
//这边还扩容了文件大小到4097，发现1000的时候不行，4096的时候正常
//
void geterror(char *s){
     perror(s);
     exit(-1) ;
}
int main(){
    char *p =NULL;
    int fd;

    fd =open("testmap",O_RDWR|O_TRUNC,0644);
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

   ftruncate(fd,20);//扩展文件大小
   int len =lseek(fd,0,SEEK_END);//获得文件大小
   //p = mmap(NULL,len,PROT_WRITE,MAP_SHARED,fd,0);//最开始正常的
   //p = mmap(NULL,len,PROT_WRITE,MAP_SHARED,fd,4096);//测试把偏移量改成1000会怎么样
   p = mmap(NULL,len,PROT_WRITE,MAP_PRIVATE,fd,0);//测试port PRIVATE
   

   if (p ==MAP_FAILED) {

    geterror("map error");

   }
    close(fd);//即便这边关闭文件描述符，也是没问题的
   //使用p对文件读写操作
    strcpy(p,"hello,mmap");
    printf("----%s\n",p);

    int ret = munmap(p,len);//释放映射区
    if (ret==-1) {

        geterror("munmap error");
    }

    return 0 ;
}
