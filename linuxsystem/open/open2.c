// File Name: open.c
// Author: wenjx
// Created Time: 2020年10月29日 星期四 20时40分47秒

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include <errno.h>
#include <string.h>
//open常见的三个错误，并且利用errno和 strerror读取错误

//打开 不存在的文件
void test01()
{

    int fd =0;
    fd = open("3.txt",O_RDONLY);

    printf("fd=%d,errno=%d:%s\n",fd,errno,strerror(errno));

    close(fd);
}
//以写方式打开只读文件，打开文件没有相应权限
void test02()
{
    int fd =0;
    fd = open("readonly.txt",O_WRONLY);
    printf("fd=%d,errno=%d:%s\n",fd,errno,strerror(errno));
    close(fd);

}
void test03()
{
    int fd =0;
    fd = open(".",O_WRONLY);//写方式打开目录
    printf("fd=%d,errno=%d:%s\n",fd,errno,strerror(errno));
    close(fd);

}
int main(){


    //test01();//打开不存在的文件报错
    //test02();//以写方式打开只读文件报错
    test03();//写方式打开目录

    return 0 ;
}
