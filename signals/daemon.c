// File Name: daemon.c
// Author: wenjx
// Created Time: 2020年11月20日 星期五 10时38分14秒

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
//守护进程创建
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
int main(){
    pid_t pid;
    pid = fork();
    int ret,fd;
    if (pid>0) {
        exit(0);//父进程终止
    }
    pid =  setsid();//创建新会话
    if (pid==-1) {

        sys_err("setsid error");
    }
    ret =chdir("../../");//改变工作目录,其实不是必要的
    if (ret==-1) {
        sys_err("chdir error");
    }
    umask(0022);//改变文件访问权限掩码,二进制反码是755

    close(STDIN_FILENO);//关闭文件描述符0

    fd =  open("/dev/null",O_RDWR);//这样fd--->0
    if (fd==-1) {
        sys_err("open error");
    }
    dup2(fd,STDOUT_FILENO);//重定向
    dup2(fd,STDERR_FILENO);

    while(1) ; //模拟守护进程 业务

    return 0 ;
}
