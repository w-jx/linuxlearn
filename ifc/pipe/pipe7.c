// File Name: pipe7.c
// Author: wenjx
// Created Time: 2020年10月31日 星期六 12时37分11秒

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
//兄弟进程通信
int main(){

    pid_t pid,wpid,pidtemp;
    int fd[2];
    int i;
    int status;
    int ret= pipe(fd);

    if (ret==-1) {

        perror("pipe error");
        exit(-1);

    }
    for(i=0;i<2;i++) {//创建两个子进程，子进程之间为兄弟进程

        pid  =fork();

        if (pid==0)
            break;
    }
    if (i==0) {

        sleep(1);
        printf("i am %d child\n",getpid());
        close(fd[0]);//关闭读端
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
    }
    else if (i==1) {
        printf("i am %d child\n",getpid());
        close(fd[1]);//关闭写端
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);

    }
    else if (i==2) {//父进程
     /*
      *四种现象：第一种不关闭父进程管道的读写端
      第二种，只关闭父进程的读端
      第三种，只关闭父进程的写端
      第四种，同时关闭父进程的读写端
      分别观察现象
      第一种光标闪烁
      第二种光标闪烁
      第三种正常
      第四种正常，结论是只要关闭父进程的写端，保证数据的单向流动即可
      *
      * */
      // close(fd[0]);
        close(fd[1]);
        // while( (wpid ==wait(NULL)) !=-1 ) {
        //   printf("parent,child%d\n",wpid);

        // }

        int wpid1,wpid2;
        wpid1  =wait(NULL);
        printf("wpid1=%d\n",wpid1);
        wpid2  =wait(NULL);
        printf("wpid2=%d\n",wpid2);

    }
    return 0 ;
}
