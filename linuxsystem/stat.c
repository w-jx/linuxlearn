// File Name: stat.c
// Author: wenjx
// Created Time: 2021年01月07日 星期四 08时07分52秒

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
    struct stat sb;
    int ret = stat(argv[1],&sb);
    if (ret!=0) 
        geterror("stat error\n");

    printf("the file size=%ld\n",sb.st_size);
    if (S_ISLNK(sb.st_mode))
        printf("FILE IS sym link\n");
    if (S_ISREG(sb.st_mode))
        printf("FILE IS REG\n");
    else if (S_ISDIR(sb.st_mode))
        printf("FILE IS dir\n");


    return 0 ;
}
