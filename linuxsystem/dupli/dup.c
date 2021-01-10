#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
//dup复制文件描述符测试
int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR|O_APPEND);       // 012  --- 3

    int newfd = dup(fd);    // 4

    printf("newfd = %d\n", newfd);
    char buf[1024]="wenjx1000000";
    write(newfd,buf,strlen(buf));

	return 0;
}
