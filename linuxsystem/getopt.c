// File Name: argc.c
// Author: wenjx
// Created Time: 2021年01月06日 星期三 15时58分39秒

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

void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(int argc,char *argv[]){//返回值为int,带参数的main函数
    /*
     *
argc:命令行参数的个数
argv:字符串数组，用来存放指向的字符串参数的指针数组

argv[0]指向程序运行的全路径名
argv[1]指向在DOS命令行中执行程序名后的第一个字符串
argv[2]指向执行程序名后的第二个字符串
argv[3]指向执行程序名后的第三个字符串
argv[argc]为NULL

     *
getopt 测试     * */
    printf("argc =%d\n",argc);
    int i;
    //for (i = 0; i < argc; i++)
    //  printf("Argument %d is %s\n", i, argv[i]);
      int ch;
        opterr = 0;
       
        while((ch = getopt(argc,argv,"a:bcde"))!= -1)
        {
            switch(ch)
            {
                case 'a': printf("option a:’%s’\n",optarg); break;
                case 'b': printf("option b :b\n"); break;
                default: printf("other option :%c\n",ch);
            }
            printf("optopt +%c\n",optopt);
        } 
    return 0;

}
