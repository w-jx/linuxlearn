// File Name: print.c
// Author: wenjx
// Created Time: 2020年12月02日 星期三 21时31分27秒

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
int main(){
    printf("this is a print test process\n");
    return 0 ;
}
