// File Name: open.c
// Author: wenjx
// Created Time: 2020年10月29日 星期四 20时40分47秒

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/socket.h>

int main(){
    int fd =0;


    open("1.txt",O_RDONLY|O_CREAT|O_TRUNC,0644);




return 0 ;
}
