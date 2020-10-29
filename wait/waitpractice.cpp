#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>
#include <sys/wait.h>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//练习，wait
int main()
{
    pid_t pid,wpid;
    int i;

    for(i=0;i<3;i++) {

        pid=fork();

        if (pid==0)
            break;

    }

    if (i==0) {

        sleep(i);
        int fd;

        fd = open("1.txt",O_RDWR);
        dup2(fd,STDOUT_FILENO);
        printf("ps aux调用\n");
        execlp("ps","ps","aux",NULL);

    }
    else if (i==1) {

        sleep(i);
        execl("./test","test",NULL);
        perror("execl error");
        exit(1);

    }
    else if (i==2) {//错误的程序

        sleep(i);
        std::vector<int> v;
        std::cout<<"v[1]="<<v[1]<<std::endl;

    }

    else  {//父进程回收子线程

        sleep(i);
        int status;
        pid_t wpid;

        while ( (wpid =wait(&status)) !=-1 )
        {
            std::cout<<"wpid="<<wpid<<std::endl;

            if ( WIFEXITED(status) ) {

                printf("return value %d\n",WEXITSTATUS(status));

            }
            else if ( WIFSIGNALED(status) ) {

                printf("died by signal %d\n",WTERMSIG(status));

            }

        }

    }

    return 0;
}
