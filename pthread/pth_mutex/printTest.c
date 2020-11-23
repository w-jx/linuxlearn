// File Name: printTest.c
// Author: wenjx
// Created Time: Sun Nov 22 07:33:42 2020

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
#include <pthread.h>
//w输出测试，我们希望父子线程能够完整输出大写HELLO,WORLD
//或者小写hello,world，在换行
void sys_err(char *s){
    perror(s);
    exit(-1) ;
}
void * tfn(void *arg) {
    srand(time(NULL));
    while (1) {
        printf("hello");
        sleep(rand()%3);
        printf(",world!\n");
        sleep(rand()%3);

    }
    return NULL;

}
int main(){
    pthread_t tid;
    int ret;

    ret =pthread_create(&tid,NULL,tfn,NULL);
    srand(time(NULL));
    if (ret!=0) {
        fprintf(stderr,"pthc_cre error=%s\n",strerror(ret));
        exit(1);
    }
    while (1) {
        printf("HELLO");
        sleep(rand()%3);
        printf(",WORLD!\n");
        sleep(rand()%3);
    }
    pthread_join(tid,NULL);

    return 0 ;
}
