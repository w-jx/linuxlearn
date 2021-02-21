// File Name: myls3.c
// Author: wenjx
// Created Time: 2021年01月09日 星期六 09时07分24秒

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include <dirent.h>
//和老师ls-R.c实现一样功能的
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
void is_dir(char *path) {//判断给定目录是不是一个文件

    struct stat sb;

    int ret = stat(path,&sb);

    if (ret!=0) {
        if (ret==ENOENT) {
            printf("the path:%s not exist\n",path);
        }
        else if (ret=EFAULT) {
            printf("the path:%s not exist2\n",path);

        }
        perror("stat error");//就因为这两句话没有加，所以程序一直出现错误
        return;
    }
    if (S_ISDIR(sb.st_mode))
        read_dir(path);
    else 
        printf("%s-----size:%ld\n",path,sb.st_size);
    return;

}
void read_dir(char *path)
{
    int ret=0;
    char pathname[256];
    DIR *dir =opendir(path);
    if (dir==NULL) {
        perror("opendir error");
        return ;
    }
    struct dirent * dirnode;
    int i=0;
    while ( dirnode =readdir(dir)) {
        if((strcmp(dirnode->d_name,".."))==0)
            continue;
        if((strcmp(dirnode->d_name,"."))==0)
            continue;
        sprintf(pathname,"%s/%s",path,dirnode->d_name);
        is_dir(pathname);

    }
    printf("\n");

    closedir(dir);//关闭目录
    return ;
}
int main(int argc,char **argv){
    char *buf;
    if (argc==1) 
        buf=".";
    else 
        buf=argv[1];
    is_dir(buf);

    return 0;
}
