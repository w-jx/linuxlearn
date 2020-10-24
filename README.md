# linuxlearn
# linux系统编程学习

## 目录

### 1.exectest文件夹

#### 	1.psaux.c

​			利用execlp函数将 ps aux命令的输出结果输出的ps.out文件中

### 2.fork文件夹

#### 	1.forktest2.cpp

​		循环创建5个子进程

#### 	2.forktest3.cpp

​		 进程共享,父子进程遵循读时共享,写时复制原则

### 3.wait文件夹

#### 	1.wait.cpp

​		利用wait(int &status)回收子进程,回收成功返回值回收子进程pid,否则为-1

#### 	2.waitreason.cpp

​		利用wait(int *status)回收子进程,如果回收成功情况下,可以利用一些宏来获取子进程退出原因	

​		常见的有WIFEXITED(status),WEXITSTATUS(status)----正常退出,WEXITSTATUS(status)返回子进程返回值

​		WIFSIGNALED(status),WTERMSIG(status)---由信号结束,WTERMSIG(status)返回杀死进程的信号id

#### 	3.waitreason2.cpp

​		利用wait(nullptr)来回收子进程,不关心子进程死亡原因,参数指针为空指针nullptr

#### 	4.waitpid092.cpp

​		利用waitpid(-1,NULL,WNOHANG);回收子进程,参数1为-1时回收任意子进程,相当于wait,而且这段程序子进程sleep,父进程不sleep，就可以回收失败，返回值是0

#### 	5.waitpid093.cpp

​		利用waitpid(pid,NULL,WNOHANG)；回收指定pid的线程，父进程在子进程之后执行完毕才能够回收,但*<u>是我这边运行提示waitpid error,回收失败，问题待解决</u>*

#### 	6.waitpid4.cpp

​		解决waitpid093.cpp的问题，回收指定pid的线程，之前的pid在子进程中pid=getpid(),在父进程回收得不到该pid值。所以用下面的代码处理：这样的tempid一定是第三个子进程的pid

```cpp
 13     for (i=0; i < 5; i++) {
 14         pid = fork();
 15 
 16         if (pid==0)//fork()函数子进程返回0，
 17             break;
 18 
 19          if (i==2 ){
 20                tempid = pid;//父进程得到子进程pid 
 21             }
 22         

```

​		还有waitpid的使用细节，WNOHANG是非阻塞的意思，如果执行waitpid时子进程尚未结束，那么会返回0，因为为了成功回收，可以用下面的两种方式：方式1：

```cpp
 26         sleep(5);
 27         wpid=waitpid(tempid,NULL,WNOHANG);//指定一个进程回收，非阻塞模式
			//注：子进程有sleep（i<5）,这种方式等待所有子进程执行结束一起回收
```

方式1执行效果：

```cpp
i am 1th child,pid=22486
i am 2th child,pid=22487
i am 3th child,pid=22488
i am 4th child,pid=22489
i am 5th child,pid=22490
parent process,wait a child finish:22488
```

方式2及方式2执行效果：

```cpp
 26         //    sleep(5);
 27         wpid=waitpid(tempid,NULL,0);//指定一个进程回收,阻塞模式
//运行结果
wenjx@ubuntu:~/Desktop/linuxlearn/wait$ ./waitpid4
i am 1th child,pid=23112
i am 2th child,pid=23113
i am 3th child,pid=23114
parent process,wait a child finish:23114
wenjx@ubuntu:~/Desktop/linuxlearn/wait$ i am 4th child,pid=23115
i am 5th child,pid=23116

```

#### 	7.waitpid5.cpp

​		waitpid回收多个子进程，利用循环，我自己的写法就是在waitpid4.cpp的基础上，把所有的子进程pid存储了，然后在利用for循环依次取出来回收

#### 	8.waitpid6.cpp

​		不需要提前存储，把wpid  =waitpid(-1,null ,options)作为循环条件进行子进程回收，也可以实现回收多个子进程

​	9.waitpractice.cpp

​		练习题：父进程fork3个子进程，三个子进程，一个调用ps命令，一个调用自定义程序1（正常），一个调用自定义程序2（会出现错误），父进程利用waitpid对其子进程进行回收