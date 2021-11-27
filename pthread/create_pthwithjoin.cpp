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
#include <pthread.h>
#include <cstdio>
//之前创建线程，主线程必须要sleep,否则就会出现子线程来不及执行的情况
//现在通过join 解决
void* tfn(void *arg)
{
    printf("thread:pid=%d,tid=%lu,\n",getpid(),pthread_self());
    return nullptr;
}

int main()
{
    pthread_t tid;
    int ret = 0;
    ret = pthread_create(&tid,nullptr,tfn,nullptr);
    if (ret!=0) {
        perror("error occured");
        return 0;
    }
    pthread_join(tid,nullptr);
    printf("in main after join :pid=%d,tid=%lu,\n",getpid(),pthread_self());
}