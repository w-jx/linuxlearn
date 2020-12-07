// File Name: lseek_file.c
// Author: wenjx
// Created Time: Sun Nov 29 20:00:36 2020

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
//利用truncate扩展文件大小
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
int main(){
    int ret = truncate("truncate_test.txt",30);//文件原来大小为10
    if (ret!=0) 
        sys_err("file open error\n");
    //int lens =  lseek(ret,0,SEEK_END);
    //printf("file lens=%d\n",lens);
    //close(ret);
    return 0 ;
}
