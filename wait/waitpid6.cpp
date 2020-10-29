#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>
#include <sys/wait.h>
#include <vector>
//回收多个子进程测试
int main()
{
    pid_t pid,wpid;  
    int i; 

    for (i=0; i < 5; i++) {
        pid = fork();

        if (pid==0)//fork()函数子进程返回0，
            break;
    }

    if (5==i) {
        sleep(5);
        while ( (wpid=waitpid(-1,NULL,WNOHANG)) !=-1 ){//无差别回收
            std::cout<<"parent process,wait a child finish:"<<wpid<<std::endl;;
        }
    }

    else {
        sleep(i);
        printf("i am %dth child,pid=%d\n",i+1,getpid());
    }


    return 0;
}
