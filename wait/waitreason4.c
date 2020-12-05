#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <sys/wait.h>
//2020/12/04复习，execlp执行kill命令，就不用另外开终端来杀进程了
int main()
{
    int status=0;
    int ret;
    pid_t pid;
    pid = fork();

    if (pid==0) {
        pid_t pidc = getpid();
        printf("this is child,pid=%d\n",pidc);
        sleep(7);
        char stri[BUFSIZ];
        sprintf(stri,"%d",pidc);
        execlp("kill","kill","-9",stri,NULL);

        return 25;//给一个不一样的返回值
    }
    else if (pid>0) {
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
