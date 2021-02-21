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
int is_dir(char *path) {//判断给定目录是不是一个文件

    struct stat sb;

    int ret = stat(path,&sb);
    
    if (ret!=0) {
        if (ret==ENOENT) {
            printf("the path:%s not exist\n",path);
        }
        else if (ret=EFAULT) {
            printf("the path:%s not exist2\n",path);

        }
        geterror("stat error");


    }
    if (S_ISDIR(sb.st_mode))
        return 1;
    else 
        return 0;

}
void read_dir(char *path)
{
    strcat(path,"/");
    printf("path=%s\n",path);
    int ret=0;
    DIR *dir =opendir(path);
    if (dir==NULL)
        geterror("opendir error");
    struct dirent * dirnode;
    int i=0;
    struct stat sb;
    char *fulldir;
    while ( dirnode =readdir(dir)) {
        if(dirnode->d_name[0]=='.')
            continue;
        if((strcmp(dirnode->d_name,".."))==0)
            continue;
        //strcat(path,dirnode->d_name);
        //printf("path dirnode->d_name=%s\n",path);

        //ret =stat(dirnode->d_name,&sb);
        //if (ret!=0)
        //    geterror("stat error");
        //if (S_ISDIR(sb.st_mode))
        //{
        //    printf("dir path=%s\n",dirnode->d_name);
        //    read_dir(path);
        //    printf("\n");
        //}

        printf("stat d_name=%s\t",dirnode->d_name);
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
        i++;
        if(i%5==0)
            printf("\n");

    }
    printf("\n");

    closedir(dir);//关闭目录
}
int main(int argc,char **argv){
    //if(!argv[1])
    //    argv[1]="./";
    //chdir(argv[1]);
    //char buf[1024];
    //getcwd(buf,sizeof(buf));
    ////printf("buf=%s",buf);
    //read_dir(buf); 
    //printf("\n");

    //int ret = is_dir(argv[1]);
    //if (ret==1)
    //    printf("is dir \n");
    //else
    //    printf("is not  dir \n");
    char *path;
    if(argc==1) 
        path = "./";//说明没有指定路径
    else
        path =argv[1];
    DIR *dir =opendir(path);
    if (dir==NULL)
        geterror("opendir error");
    struct dirent * dirnode;
    int i=0;
    int ret=0;
    while ( dirnode =readdir(dir)) {
        char * statpath;
        sprintf(statpath,"%s%s",path,dirnode->d_name);
        int ret=is_dir(statpath);
        if(ret!=1) 
            printf("%s\t",dirnode->d_name);
        else {

        if(dirnode->d_name[0]=='.')
            continue;
        if((strcmp(dirnode->d_name,".."))==0)
            continue;

        sprintf(path,"%s/%s",path,dirnode->d_name);
        main(2,&path);
        }

    }

    return 0;
}
