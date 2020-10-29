// File Name: forktest.c
// Author: xiaxiaosheng
// Created Time: 2020年10月29日 星期四 11时42分07秒

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

int main(){
    pid_t pid;
    printf("xxxxxxxxxxxx\n");
    int i;
    for(i=0;i<5;i++){
        pid = fork();
        if(pid == -1){
            perror("fork erro:");
            exit(-1);
        }else if(pid == 0){
            break;
        }
    }

    if(i<5){
        sleep(i);
        printf("I am %d child,pid = %u\n",i+1,getpid());
    }else{
        sleep(i);
        printf("I am parnet\n");
    }
    //printf("yyyyyyyyyy\n");
    return 0;
}
