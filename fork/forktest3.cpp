#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>

int var = 100;

void test01()//写时复制
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork error\n");
        exit(1);
    }

    else if (pid > 0)
    {
        var = 288;
        std::cout << "parentprocess,var=" << var << ",pid()" << getpid() << ",ppid()=" << getppid() << std::endl;
    }
    else if (0 == pid)
    {
        var = 200;
        std::cout << "childprocess,var=" << var << ",pid()" << getpid() << ",ppid()=" << getppid() << std::endl;
    }
}
void test02()//读时共享
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork error\n");
        exit(1);
    }

    else if (pid > 0)
    {
        //var = 288;
        std::cout << "parentprocess,var=" << var << ",pid()" << getpid() << ",ppid()=" << getppid() << std::endl;
    }
    else if (0 == pid)
    {
        //var = 200;
        std::cout << "childprocess,var=" << var << ",pid()" << getpid() << ",ppid()=" << getppid() << std::endl;
    }
}
int main()
{
    //test01();
    test02();
    return 0;
}
