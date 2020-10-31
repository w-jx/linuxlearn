// File Name: pipe1.cpp
// Author: xiaxiaosheng
// Created Time: 2020年10月28日 星期三 20时20分57秒

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//pipe 练习，使用管道实现父子进程通信，完成ls |wc -l
int main(){

    int ret;
    int fd[2];

    pid_t pid;

    ret  =pipe(fd);

    char * str = "hellp,world\n";
    char buf[20];

    pid=fork();

    if (pid==0 ) { //子进程

        close(fd[0]);//关闭读
        dup2(fd[1],STDOUT_FILENO);//
        sleep(1);//这个sleep没有作用，因为子进程阻塞等待，父进程永远先结束
        //会出现子进程竞争不过父进程bash的情况
        execlp("ls","ls",NULL);
        // sleep(2);//execlp执行成功下面的不执行，除非出错
        //close(fd[1]);//同理
    }
    else if (pid>0) {//父进程

        close(fd[1]);//关闭写 端
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        // close(fd[0]);这边不应该close(fd[0]),因为execlp执行成功不往下面走，除非出错
    }
    return 0;
}
