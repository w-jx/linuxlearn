# linuxlearn
# linux系统编程学习

## 目录

### 1.exectest文件夹

​		1.psaux.c:利用execlp函数将 ps aux命令的输出结果输出的ps.out文件中

### 2.fork文件夹

​	1.forktest2.cpp

​		循环创建5个子进程

​	2.forktest3.cpp

​		 进程共享,父子进程遵循读时共享,写时复制原则

### 3.wait文件夹

​	1.wait.cpp

​		利用wait(int &status)回收子进程,回收成功返回值回收子进程pid,否则为-1

​	2.waitreason.cpp

​		利用wait(int *status)回收子进程,如果回收成功情况下,可以利用一些宏来获取子进程退出原因	

​		常见的有WIFEXITED(status),WEXITSTATUS(status)----正常退出,WEXITSTATUS(status)返回子进程返回值

​		WIFSIGNALED(status),WTERMSIG(status)---由信号结束,WTERMSIG(status)返回杀死进程的信号id

​	3.waitreason2.cpp

​		利用wait(nullptr)来回收子进程,不关心子进程死亡原因,参数指针为空指针nullptr

​	4.waitpid092.cpp

​		利用waitpid(-1,NULL,WNIHANG);回收子进程,参数1为-1时回收任意子进程,相当于wait