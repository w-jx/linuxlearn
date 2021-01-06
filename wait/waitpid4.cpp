#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>
#include <sys/wait.h>
//错误解析，对waitpid093问题解决
int main()
{
    pid_t pid,wpid,tempid;  
    int i; 

    for (i=0; i < 5; i++) {
        pid = fork();

        if (pid==0)//fork()函数子进程返回0，
            break;

        if (i==2 ){
            tempid = pid;//父进程得到子进程pid 
        }

    }

    if (5==i) {
        //    sleep(5);
        wpid=waitpid(tempid,NULL,0);//指定一个进程回收,阻塞模式
        if (wpid==-1){
            perror("waitpid error");
            exit(1);
        }
        std::cout<<"parent process,wait a child finish:"<<wpid<<std::endl;;
    }
    else {
        sleep(i);
        printf("i am %dth child,pid=%d\n",i+1,getpid());
    }

}

