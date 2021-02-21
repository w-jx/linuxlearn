#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("open error");
        exit(1);
    }
    printf("fd1 = %d\n",fd1);

    int fd2 = fcntl(fd1, F_DUPFD, 0);
    if (fd2 < 0) {
        perror("fcntl error");
        exit(1);
    }
    printf("fd2 = %d\n",fd2);

    int fd3 = fcntl(fd1, F_DUPFD, 18);
    if (fd3 < 0) {
        perror("fcntl error");
        exit(1);
    }

    printf("fd3 = %d\n",fd3);

    char buf[10];

    int n = read(fd3, buf, 10);
    if (n < 0) {
        perror("read error"); 
        exit(1);
    }

    printf("%d read:%s\n", fd3, buf);
    printf("--------------------\n");

	return 0;
}
