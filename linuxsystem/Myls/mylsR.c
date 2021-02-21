// File Name: myls.c
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
#define CMD "./ ~//Desktop//linuxlearn//linuxsystem//mylsR"
//ls -R 功能的实现
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
int main(int argc,char **argv){
    if(!argv[1])
        argv[1]="./";
    int ret = chdir(argv[1]);//改变目录
    if(ret!=0)
        geterror("chdir error");
    DIR * dir = opendir(argv[1]);//
    if (dir==NULL)
        geterror("opendir error");
    char buf[1024];
    getcwd(buf,sizeof(buf));
    //printf("current cwd=%s\n",buf);
    strcat(buf,"/");
    struct dirent * dirnode;
    int i=0;

    struct stat sb;
    while ( dirnode =readdir(dir)) {
        if (dirnode->d_name[0]=='.')
            continue;
        if ((strcmp(dirnode->d_name,".."))==0)
            continue;
        printf("-----current file/dir=%s\n",dirnode->d_name);
        char *fulldir = strcat(buf,dirnode->d_name);
        printf("-----current fulldir=%s\n",fulldir);
        ret = stat(fulldir,&sb);
        if(ret!=0)
            geterror("stat error");
        if (S_ISDIR(sb.st_mode)) {
            printf("-----%s:\n",dirnode->d_name);
            //Desktop/linuxlearn/linuxsystem
            execl(CMD,CMD,dirnode->d_name,NULL);
        }
        printf("%s\n",dirnode->d_name);
        i++;
        if(i%5==0)
            printf("\n");
    }
    printf("\n");

    closedir(dir);//关闭目录
    //int x=10;
    //printf("\e[5;4;31;42mhhhhhhhh\033[0m\n");
    //printf("\e[1;31;42mx=%d\033[0m\n",x);
    return 0 ;
}
