// File Name: mychmod.c
// Author: wenjx
// Created Time: 2021年01月07日 星期四 08时43分59秒

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

void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(int argc,char **argv){
    int ret = chmod(argv[1],atoi(argv[2]));
    if(ret!=0) {

        if (errno==EACCES)
            printf("permission denied\n");
        else if (errno==EFAULT) 
            printf("pathname points outside your accessible address space\n");
        else if (errno==EIO)
            printf("I/O error\n");
    }
    else 
        printf("chmod success\n");
    return 0 ;
}
