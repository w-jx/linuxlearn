#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>

void isFile(char *name);

// 打开目录读取,处理目录
void read_dir(char *dir, void (*func)(char *))
{
    char path[256];
    DIR *dp;
    struct dirent *sdp;

    dp = opendir(dir);
    if (dp == NULL) {
        perror("opendir error");
        return;
    }
    // 读取目录项
    while((sdp = readdir(dp)) != NULL) {
        if (strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name, "..") == 0) {
            continue;
        }
        //fprintf();
        // 目录项本身不可访问, 拼接. 目录/目录项
        sprintf(path, "%s/%s", dir, sdp->d_name);

        // 判断文件类型,目录递归进入,文件显示名字/大小
        //isFile(path);    
        (*func)(path);
    }

    closedir(dp);

    return ;
}

void isFile(char *name){

    int ret = 0;
    struct stat sb;

    // 获取文件属性, 判断文件类型
    ret = stat(name, &sb);
    if (ret == -1) {
        perror("stat error");
        return ;
    }
    // 是目录文件
    if (S_ISDIR(sb.st_mode)) {
        read_dir(name, isFile);
    }
    // 是普通文件, 显示名字/大小
    printf("%10s\t\t%ld\n", name, sb.st_size);
    return;
}

int main(int argc, char *argv[])
{
    // 判断命令行参数
    if (argc == 1) {
        isFile(".");
    } else {
        isFile(argv[1]);
    }

    return 0;
}
