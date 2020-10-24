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
    std::vector<pid_t> v;
    pid_t pid,wpid,tempid;  
    int i; 

    for (i=0; i < 5; i++) {
        pid = fork();

        if (pid==0)//fork()函数子进程返回0，
            break;

       v.push_back(pid);
    }

    if (5==i) {
         sleep(5);
   
        for (auto iter: v) {

        wpid=waitpid(iter,NULL,WNOHANG);//指定一个进程回收,阻塞模式
        if (wpid==-1){
            perror("waitpid error");
            exit(1);
        }
        std::cout<<"parent process,wait a child finish:"<<wpid<<std::endl;;

        }


    }
    else {
        sleep(i);
        printf("i am %dth child,pid=%d\n",i+1,getpid());
    }


    return 0;
}
