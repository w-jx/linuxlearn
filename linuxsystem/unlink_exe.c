/*
 *unlink函数是删除一个dentry
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(void)
{
	int fd, ret;
	char *p = "test of unlink\n";
	char *p2 = "after write something.\n";

	fd = open("temp.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if(fd < 0){
		perror("open temp error");
		exit(1);
	}

	ret = unlink("temp.txt");		 //具备了被释放的条件
	if(ret < 0){
		perror("unlink error");
		exit(1);
	}

	ret = write(fd, p, strlen(p));
    if (ret == -1) {
        perror("-----write error");
    }

	printf("hi! I'm printf\n");
	ret = write(fd, p2, strlen(p2));
    if (ret == -1) {
        perror("-----write error");
    }

    printf("Enter anykey continue\n");
    getchar();

    p[3] = 'H';


	close(fd);


	return 0;
}
