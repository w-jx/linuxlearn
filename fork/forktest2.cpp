#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pid head
#include <pthread.h>
#include <iostream>

int main()
{


    pid_t pid; 
    int i = 0;

    for (; i < 5; i++)
    {
        if (fork() == 0)
            break;
    }

    if (5==i) {
        sleep(5);
        printf("parent\n");
    }
    else {
        sleep(i);
        printf("i am %dth child\n",i+1);
    }


    return 0;
}
