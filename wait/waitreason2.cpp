#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>
#include <sys/wait.h>
//获取子进程退出原因 利用宏,不关心子进程死亡原因，对应视频08获取子进程退出值和异常终止信号
//wait(nullptr)没有int* 参数
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
        return 73;//
    }
    else if (pid>0 ) {
        
        wpid = wait(nullptr);//不关心子进程死亡原因
        if (wpid == -1) {
            perror("wait error");
            exit(1);
        }

        // if ( WIFEXITED(status) )  {
        //     std::cout<<"child exit value:"<<WEXITSTATUS(status)<<std::endl;

        // }//为真，代表子进程正常结束
        // else if (WIFSIGNALED(status)) //为真，说明子进程是被信号终止
        // {
        //      std::cout<<"child kill signal:"<<WTERMSIG(status)<<std::endl;//获得终止的那个信号的id
        // }
        std::cout<<"parent wait finish："<<wpid<<std::endl;
    }
   else {
       
     perror("error in fork");
     exit(1);
   }

    return 0;
}
