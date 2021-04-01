#include <fcntl.h>
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MQNAME "/mqtest"


int main()
{

    mqd_t mqd;
    int ret;
    int val;
    char buf[BUFSIZ];

    mqd = mq_open(MQNAME, O_RDWR);
    if (mqd == -1) {
        perror("mq_open()");
        exit(1);
    }

    ret = mq_receive(mqd, buf, BUFSIZ, &val);
    if (ret == -1) {
        perror("mq_send()");
        exit(1);
    }

    ret = mq_close(mqd);
    if (ret == -1) {
        perror("mp_close()");
        exit(1);
    }

    printf("msq: %s, prio: %d\n", buf, val);

    exit(0);
}