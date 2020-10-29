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
    printf("ps aux调用\n");
    execlp("ps","ps","aux",">","1.txt",NULL);


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

    switch(pid)
    {

        case 0:
            pscall();
            break;
        case 1:
            print();
            break;
        case 2:
            myvector();
            break;
        case 3:
            printf("parent\n");
        default:
            break;
    }


    return 0;
}
