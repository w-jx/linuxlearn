#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#define MAX_SIZE 100
#define SHM_KEY_T 9494
#define SEM_KEY_T 8989

typedef struct SHM_BLOCK
{
    int semid;
    int dataCount;
    int beginPos;
    int curPos;
    char data[MAX_SIZE];
};

void childProcess();
void parentProcess();
SHM_BLOCK  *block;  //下面要用到的指向共享内存的指针
struct sembuf buf; //操作信号量的结构体
int pid;           //用于存储子进程的pid
int shmid;         //共享内存的id
int main()
{
        shmid = shmget(SHM_KEY_T, sizeof(SHM_BLOCK), 0600 | IPC_CREAT);
        block = (SHM_BLOCK *)shmat(shmid, (const void *)0, 0);
        block->semid = semget(SEM_KEY_T, 1, 0600 | IPC_CREAT);
        block->dataCount = 0;
        block->beginPos = 0;
        block->curPos = 0;
        semctl(block->semid, 0, SETVAL, 1); //初始化信号量，赋值为1
        pid = fork();
        if (pid == 0)
        childProcess();
        else         parentProcess();
        return 0;
}
void childProcess()
{
    printf("Im child  Process pid is %d lets begin do work\n", getpid());
    getchar();
        int taskCount = 0;
        char task;
        block = (SHM_BLOCK *)shmat(shmid, (const void *)0, 0);
        buf.sem_flg = 0;
        buf.sem_num = 0;
        while (taskCount < 200)
    {
            buf.sem_op = -1;
            semop(block->semid, &buf, 1);
            buf.sem_op = 1;
            if (block->dataCount == 0)
        {
                    semop(block->semid, &buf, 1);
                    continue;
               
        }
            block->dataCount--;
            task = block->data[block->beginPos++];
            block->beginPos %= MAX_SIZE;
            semop(block->semid, &buf, 1);
            taskCount++;
            printf("Cur Task is %d   the data is %c\n", taskCount, task);
           
    }
        shmdt((const void *)block);
        return;
}

void parentProcess()
{
        printf("Im parent Process pid is %d lets begin add work\n", getpid());
        getchar();
        buf.sem_flg = 0;
        buf.sem_num = 0;
        int taskCount = 0;
        while (taskCount < 200)
    {
                buf.sem_op = -1;
                semop(block->semid, &buf, 1);
                buf.sem_op = 1;
                if (block->dataCount >= MAX_SIZE)
       
        {
                        semop(block->semid, &buf, 1);
                        continue;
                   
        }
                block->dataCount++;
                block->data[block->curPos++] = 'a' + taskCount % 26;
                block->curPos %= MAX_SIZE;
                semop(block->semid, &buf, 1);
                taskCount++;
           
    }
        //回收进程资源
    waitpid(pid, NULL, 0);
        //释放调信号量和共享内存
    semctl(block->semid, 0, IPC_RMID);
        shmdt((const void *)block);
        shmctl(shmid, IPC_RMID, 0);
        return;
}
