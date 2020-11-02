// File Name: hello.c
// Author: wenjx
// Created Time: 2020年10月31日 星期六 21时27分44秒

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

int add(int ,int);
int minus(int ,int);
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(){
    int a=10;
    int b=5;
    printf("%d+%d=%d\n",a,b,add(a,b));
    printf("%d-%d=%d\n",a,b,minus(a,b));
    return 0 ;
}
