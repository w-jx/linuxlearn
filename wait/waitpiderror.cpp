#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>
#include <sys/wait.h>
//出问题版本的，12/05u复习看，因为pid不一样
int main()
{
    pid_t pid,wpid;  
    int i; 

    for (i=0; i < 5; i++) {
        if (fork() == 0){//循环期间，子进程不fork
            if (i==2 ){
                pid=getpid();
            }
            break;
        }

    }

    if (5==i) {
        sleep(5);
        wpid=waitpid(pid,NULL,WNOHANG);//指定一个进程回收，
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


    return 0;
}

