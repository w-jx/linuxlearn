// File Name: test.c
// Author: wenjx
// Created Time: Sat Dec  5 12:21:01 2020

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

void sys_err(char *s){
     perror(s);
     exit(-1) ;
}
int main(){
printf("hellomwo\n");
return 0 ;
}
