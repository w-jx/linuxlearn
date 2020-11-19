// File Name: sigcatch.c
// Author: wenjx
// Created Time: Tue Nov 17 19:41:16 2020

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
#include <signal.h>
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
void sig_catch(int signum)
{
    printf("catch you,%d\n",signum);
}
int main(){
    while(1)
        signal(SIGINT,sig_catch);

    return 0 ;
}
