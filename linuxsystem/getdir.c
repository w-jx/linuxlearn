// File Name: getdir.c
// Author: wenjx
// Created Time: 2021年01月09日 星期六 11时21分35秒
#define _GNU_SOURCE //如果不定义这句话，函数出错
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
//测试利用getcwd等函数获取当前工作目录
void geterror(char *s){
    perror(s);
    exit(-1) ;

}
void test01()//getcwd测试
{
char buf[1024];
char *ret = getcwd(buf,sizeof(buf));
printf("buf=%s\n",buf);
printf("ret=%s\n",ret);
}
void test02()//getwd测试,函数不安全，不适用
{

char buf[1024];
char *ret = getwd(buf);
printf("buf=%s\n",buf);
printf("ret=%s\n",ret);



}
void test03()//get_current_dir_name()测试
{
    char * pwd = get_current_dir_name();
    printf("pwd=%s\n",pwd);
    free(pwd);
}
int main(){
    //test01();//getcwd测试
    test02();//getwd测试
    return 0 ;
}
