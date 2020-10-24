#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>
#include <sys/wait.h>
//获取子进程退出原因 利用宏,对应视频08-获取子进程退出值和异常终止信号
/*
pid_t wait(int &status)
调试方法：pid==0,说明是子进程，给一个特别的返回值73，然后如果
是正常退出的话，利用WIFEXITED(status) 为真，WEXITSTATUS(status)获得返回值

或者：当子进程运行，利用gitpid()获得子进程pid,然后故意加延时15s,新开终端kill -9 pid，
子进程就是被信号退出的，WIFSIGNALED(status)为真，WTERMSIG(status)获得信号pid
*/
int main()
{
    pid_t pid,wpid;
    pid = fork();
    int status = 0;
    if (pid == 0)//子进程
    {
        std::cout<<"child,my id="<<getpid()<<std::endl;
        sleep(15);
        printf("child die\n");
        return 73;//
    }
    else if (pid>0 ) {
        
        wpid = wait(&status);//如果子进程没有结束，父进程阻塞
        if (wpid == -1) {
            perror("wait error");
            exit(1);
        }

        if ( WIFEXITED(status) )  {
            std::cout<<"child exit value:"<<WEXITSTATUS(status)<<std::endl;//输出的就是上面的73

        }//为真，代表子进程正常结束
        else if (WIFSIGNALED(status)) //为真，说明子进程是被信号终止
        {
             std::cout<<"child kill signal:"<<WTERMSIG(status)<<std::endl;//获得终止的那个信号的id
        }
        std::cout<<"parent wait finish："<<wpid<<std::endl;
    }
   else {
       
     perror("error in fork");
     exit(1);
   }

    return 0;
}
