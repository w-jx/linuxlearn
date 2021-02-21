// File Name: myls.c
// Author: wenjx
// Created Time: 2021年01月09日 星期六 09时07分24秒

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
#include <dirent.h>
//利用readdir等函数实现ls功能
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(int argc,char **argv){
    if(!argv[1])
        argv[1]="./";
    DIR * dir = opendir(argv[1]);//打开当前目录
    if (dir==NULL)
        geterror("opendir error");
    struct dirent * dirnode;
    int i=0;

    while ( dirnode =readdir(dir)) {
        if(dirnode->d_name[0]=='.')
            continue;
        printf("%s\t",dirnode->d_name);
        i++;
        if(i%5==0)
            printf("\n");
    }
    printf("\n");

    closedir(dir);//关闭目录
    int x=10;
    printf("\e[5;4;31;42mhhhhhhhh\033[0m\n");
    printf("\e[1;31;42mx=%d\033[0m\n",x);
    return 0 ;
}
