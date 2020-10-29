// File Name: pipe1.cpp
// Author: xiaxiaosheng
// Created Time: 2020年10月28日 星期三 20时20分57秒
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//父进程sleep,子进程read阻塞等待现象
int main(){

    int ret;
    int fd[2];

    pid_t pid;

    ret  =pipe(fd);

    char * str = "hellp,world\n";
    char buf[20];

    pid=fork();

    if (pid==0 ) { //子进程

        close(fd[1]);//关闭写 端
        ret = read(fd[0],buf,sizeof(buf));
        printf("ret=%d\n",ret);
        write(STDOUT_FILENO,buf,ret);//正确
        close(fd[0]);

    }
    else if (pid>0) {//父进程

        close(fd[0]);//关闭读
        sleep(1);//
        close(fd[1]);//关闭写端，read返回0,所以ret=0
        write(fd[1],str,strlen(str));
        close(fd[1]);
    }
    return 0;
}
