#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
static char msg[]="你好，共享内存!";
 
typedef int sem_t;
 
union semun{
	int   val;
	struct semid_ds *buf;
	unsigned short  *arry;
}arg;
 
sem_t CreateSem(key_t key,  int value)
{
	union semun sem;
	sem_t semid;
	sem.val = value;
	
	semid = semget(key, 1, IPC_CREAT|0660);
	if (semid == -1)
	{
		printf("create error!");
		return -1;
	}
 
	semctl(semid, 0, SETVAL, sem);   // 发出命令 建立value个初始值信号量
 
	return semid;
}
 
int Sem_P(sem_t semid)
{
	struct sembuf sops = {0, +1, IPC_NOWAIT};
	return (semop(semid,  &sops, 1));
}
 
int Sem_V(sem_t semid)
{
	struct sembuf sops = {0, -1, IPC_NOWAIT};
	return (semop(semid,  &sops, 1));
}
 
int GetvalueSem(sem_t semid)
{
	union semun sem;
	sem.val = 0;
	return semctl(semid, 0, GETVAL, sem);
	
}
 
void DestroySem(sem_t semid)
{
	union semun sem;
	sem.val = 0;
	semctl(semid, 0, IPC_RMID, sem);
}
 
 
int main(void)
{
	key_t key;
	int semid, shmid;
	char i, *shms, *shmc;
	struct semid_ds buf;
	int value = 0;
	char buffer[80];
	pid_t p;
 
	key = ftok("./server.c", 'a');
	shmid = shmget(key, 1024, IPC_CREAT|0660);  // 获得共享内存，大小为1024个字节
	semid = CreateSem(key,0);    // 创建信号量 实现互斥访问
 
	p = fork();
	if (p > 0)
	{
		shms = (char*)shmat(shmid, 0,0);
		memcpy(shms, msg, strlen(msg)+1);
		sleep(10);
		Sem_P(semid);
		shmdt(shms);
 
		DestroySem(semid);
	}
	else if (p == 0)
	{
		shmc = (char*)shmat(shmid, 0,0);
		Sem_V(semid);
		printf("Memory:%s\n", shmc);
		shmdt(shmc);
	}
	return 0;
}