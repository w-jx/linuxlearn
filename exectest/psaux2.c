// File Name: psaux2.c
// Author: xiaxiaosheng
// Created Time: 2020年10月29日 星期四 12时13分12秒

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
void test01()
{

    int fd = open("1.txt",O_RDWR);

    dup2(fd,STDOUT_FILENO);
    execlp("ps","ps","aux",NULL);



}
int main(){
    test01();
    return 0 ;
}
