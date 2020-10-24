#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>
#include <sys/wait.h>
#include <vector>
//回收多个子进程测试

//第一个子进程调用ps命令
void pscall() 
{
 execlp("ps","ps","aux",NULL);


}
//第二个子进程调用正常程序
int print()
{
    std::cout<<"heello,world\n";
    return 28;

}
//第三个子进程调用一个会出错的程序
void myvector()
{
    std::vector<int> v;

    std::cout<<"v[1]="<<v[1]<<std::endl;
}
int main()
{
    pid_t pid,wpid;
    int i;

    for(i=0;i<3;i++) {


    pid=fork();

    if (pid==0)
        break;
    }
    if (3==i) {

    
        sleep(



    }
    
    std::vector<pid_t> v;
    pid_t pid,wpid,tempid;  
    int i; 

    for (i=0; i < 5; i++) {
        pid = fork();

        if (pid==0)//fork()函数子进程返回0，
            break;

    }

    if (5==i) {
        // sleep(5);
   
     
  
        while (wpid=waitpid(-1,NULL,0) ){//指定一个进程回收,非阻塞模式
           
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
