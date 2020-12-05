#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <sys/wait.h>
//2020/12/04复习，wait回收子进程原因
int main()
{
    int status=0;
    int ret;
    pid_t pid;
    pid = fork();

    if (pid==0) {

        printf("this is child,pid=%d\n",getpid());
        sleep(1);

        return 25;//给一个不一样的返回值
    }
    else if (pid>0) {
        //char stri[BUFSIZ];
        //sprintf(stri,"%d",pid);
        //execlp("kill","kill","-9",stri,NULL);
        ret = wait(&status);
        if (ret!=-1) {

            if (WIFEXITED(status)) {//正常原因退出
                printf("child %d exit with retvalue=%d\n",pid,WEXITSTATUS(status));

            }
            else if (WIFSIGNALED(status) ) 
                printf("child %d exited by a signal:%d\n",pid,WTERMSIG(status));

        }
        else {
            perror("wait error");
            exit(1);
        }
        printf("this is parent process\n");

    }

    return 0;

}
