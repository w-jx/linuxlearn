// File Name: pipe1.cpp
// Author: xiaxiaosheng
// Created Time: 2020年10月28日 星期三 20时20分57秒

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
        write(STDOUT_FILENO,buf,ret);//正确
        close(fd[0]);

    }
    else if (pid>0) {//父进程

        close(fd[0]);//关闭读
        sleep(3);//
        write(fd[1],str,strlen(str));
        close(fd[1]);
    }
    return 0;
}
