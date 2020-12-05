#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>
#include <wait.h>

int main()
{
    pid_t pid,wpid;
    pid = fork();
    int status = 0;
    if (pid == 0)//子进程
    {
        std::cout<<"child,my id="<<getpid()<<std::endl;
        sleep(10);
        printf("child die\n");
    }
    else if (pid>0 ) {
        
        wpid = wait(&status);//子进程没有死亡，阻塞在这边
        if (wpid == -1) {
            perror("wait error");
            exit(1);
        }
        std::cout<<"parent wait finish："<<wpid<<std::endl;
    }
   else {
       
     perror("error in fork");
     exit(1);
   }

    return 0;
}
