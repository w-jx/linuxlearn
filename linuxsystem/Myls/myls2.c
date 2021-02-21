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
//封装一个函数实现readdir功能
void geterror(char *s){
    perror(s);
    exit(-1) ;
}
void read_dir(char *path)
{
    strcat(path,"/");
   // printf("path=%s\n",path);
    int ret=0;
    DIR *dir =opendir(path);
    if (dir==NULL)
    {
        perror("opendir error");
        return;
    }
    struct dirent * dirnode;
    int i=0;
    struct stat sb;
    char *fulldir;
    while ( dirnode =readdir(dir)) {
        if((strcmp(dirnode->d_name,".."))==0)
            continue;
        if((strcmp(dirnode->d_name,"."))==0)
            continue;
        
        //printf("stat d_name=%s\t",dirnode->d_name);
        ret =  stat(dirnode->d_name,&sb);
        if (ret!=0)
            geterror("stat error");
        if (S_ISDIR(sb.st_mode)) {
            char *oldpwd = path;
            strcat(path,dirnode->d_name);
            chdir(path);
            read_dir(path);
            chdir(oldpwd);
        }
        else {
        printf("%s-----------size:%ld\t",dirnode->d_name,sb.st_size);
            i++;
        if(i%5==0)
            printf("\n");
        }
    }
    printf("\n");

    closedir(dir);//关闭目录
}
int main(int argc,char **argv){
    if(!argv[1])
        argv[1]="./";
    chdir(argv[1]);
    char buf[1024];
    getcwd(buf,sizeof(buf));
    read_dir(buf); 
    printf("\n");
    return 0 ;
}
