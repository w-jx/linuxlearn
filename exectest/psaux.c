// File Name: psaux.cpp
// Author: xiaxiaosheng
// Created Time: 2020年10月20日 星期二 08时59分34秒

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

    int fd;
    //fd =open("ps.out",O_WRONLY|O_CREAT|O_TRUNC,0644);
    fd =open("1.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
    if (fd<0) {
        perror("open ps.out error");
        exit(1);

    }
    dup2(fd,STDOUT_FILENO);//标准输出重定向到文件描述符中

    execlp("ps","ps","aux",NULL);


    return 0;
}
