#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>
#include <sys/wait.h>
/*
2020/10/23.waitpid回收子进程 09
*/
int main()
{


    pid_t pid; 
    int i = 0;

    for (; i < 5; i++)
    {
        if (fork() == 0)//循环期间，子进程不fork
            break;
    }

    if (5==i) {
       auto wpid =  waitpid(-1,NULL,WNIHANG);//-1相当于wait
       if (wpid==-1){
        perror("waitpid error");
        exit(1);
       }
        std::cout<<"parent process,wait a child finish:"<<wpid;
        printf("parent\n");
    }
    else {
        sleep(i);
        printf("i am %dth child\n",i+1);
    }


    return 0;
}
