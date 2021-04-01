#include <fcntl.h>
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MQNAME "/mqtest"


int main(int argc, char *argv[])
{

    mqd_t mqd;
    int ret;

    if (argc != 3) {
        fprintf(stderr, "Argument error!\n");
        exit(1);
    }

    mqd = mq_open(MQNAME, O_RDWR|O_CREAT, 0600, NULL);
    if (mqd == -1) {
        perror("mq_open()");
        exit(1);
    }

    ret = mq_send(mqd, argv[1], strlen(argv[1]), atoi(argv[2]));
    if (ret == -1) {
        perror("mq_send()");
        exit(1);
    }

    exit(0);
}