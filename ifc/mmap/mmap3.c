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
//PORT_PRIVATE测试,发现不会报错，但是对内存的修改没有反映到磁盘上
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

    ftruncate(fd,20);//扩展文件大小
    int len =lseek(fd,0,SEEK_END);//获得文件大小
    p = mmap(NULL,len,PROT_WRITE,MAP_PRIVATE,fd,0);//测试port PRIVATE

    if (p ==MAP_FAILED) {

        geterror("map error");

    }
    //使用p对文件读写操作
    strcpy(p,"hello,mmap");
    printf("----%s\n",p);

    int ret = munmap(p,len);//释放映射区
    if (ret==-1) {

        geterror("munmap error");
    }

    return 0 ;
}
