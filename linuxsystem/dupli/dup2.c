#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDWR|O_APPEND);       // 012  --- 3

    int fd2 = open(argv[2], O_RDWR|O_APPEND);       // 012  --- 3
    printf("fd1=%d,fd2=%d\n",fd1,fd2);
    int fdret = dup2(fd1, fd2);     // 返回 新文件描述符fd2
    printf("fdret = %d\n", fdret);

    int ret = write(fd2, "1234567", 7); // 写入 fd1 指向的文件
    printf("ret = %d\n", ret);

    dup2(fd1, STDOUT_FILENO);       // 将屏幕输入,重定向给 fd1所指向的文件.

    printf("-----------------------------886\n");//本来输出到屏幕上的，输出到fd1上了

	return 0;
}
