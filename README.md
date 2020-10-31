# linuxlearn
# linux系统编程学习

## 目录

### 1.exectest文件夹

#### 	1.psaux.c

​			利用execlp函数将 ps aux命令的输出结果输出的ps.out文件中，注意dup2重定向文件描述符函数的简单使用：

```cpp
int dup2(int odlfd, int newfd);
```

​			dup2()用来复制参数oldfd 所指的文件描述词, 并将它拷贝至参数newfd 后一块返回. 若参数newfd为一已打开的文件描述词, 则newfd 所指的文件会先被关闭. dup2()所复制的文件描述词, 与原来的文件描述词共享各种文件状态, 详情可参考dup().

​			正常执行execlp("ps","ps","aux",NULL)会在命令行中输出，我们想要将输出结果显示在文件中，首先需要打开文件，然后重定向文件描述符

```cpp
int fd = open();//打开文件
dup2(fd,STDOUT_FILENO);//重定向标准输出
execlp("ps","ps","aux",NULL);
```

 

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

#### 9.waitpractice.cpp
​		练习题：父进程fork3个子进程，三个子进程，一个调用ps命令，一个调用自定义程序1（正常），一个调用自定义程序2（会出现错误），父进程利用waitpid对其子进程进行回收

​		1.for循环创建三个线程

```cpp
 18     for(i=0;i<3;i++) {
 20         pid=fork();
 22         if (pid==0)
 23             break;
 25     }   
```

​		2.根据i==0,1,2执行子线程的程序

​		3.i==3是父线程，进行回收，利用宏来得到线程退出原因	

```cpp
 60         while ( (wpid =wait(&status)) !=-1 )
 61         {
 62             std::cout<<"wpid="<<wpid<<std::endl;
 63 
 64             if ( WIFEXITED(status) ) {
 65 
 66                 printf("return value %d\n",WEXITSTATUS(status));
 67 
 68             }
 69             else if ( WIFSIGNALED(status) ) {
 70 
 71                 printf("died by signal %d\n",WTERMSIG(status));
 72 
 73             }
 74 
 75         }

```

​	



### 4.ifc文件夹----进程间通信

#### 	1.pipe文件夹

##### 			1.pipe1.c 

​					利用pipe(int [])创建管道，利用fork()函数创建子线程，在父线程中写，在子线程中读，然后输出到				bash中。

##### 			2.pipe2.c

​					父进程阻塞，然后子进程read时管道中无数据，但是管道写端没有被关闭，因此read阻塞等待

##### 			3.pipe3.c

​					 在ret后面添加输出，可以得到正常情况下输出12，是父进程写的字符长度，现在在父进程sleep(3)后面添加关闭写管道，观察返回ret返回0的现象（注意事项：如果sleep(1)，时间改成1，这样就可能会出现ret=0,然后bash命令提示符闪烁，因为子进程没有竞争过父进程的bash）

##### 4.pipe4.c

​					练习：使用管道实现父子进程间通信，完成ls|wc-l，实现的第一个版本，小问题就是执行成功了bash没有结束，光标闪烁。(问题出在execlp("wc","-l",NULL),忘了一个"wc")

​	![image-20201031094803769](/home/wenjx/.config/Typora/typora-user-images/image-20201031094803769.png)

##### 5.pipe5.c

​				练习的改进版，ls下有10个文件，程序的执行结果是10，新问题是子进程总是竞争不过父进程的bash,原因在于父进程写端没有关闭时，子进程读端阻塞等待，不管父进程加不加sleep都是父进程先结束，目前的解决方法只有让子进程ls，父进程wc-l。

##### 6.pipe6.c

​				父子进程的程序颠倒，子进程ls，父进程wc-l解决问题。

### 5.linuxsystem文件夹--前面linux系统基础知识

#### 	1.open文件夹

##### 			1.open.c

​					利用open()创建文件，配合O_RDONLY,O_CREAT代表文件不存在时候创建文件，O_TRUNC代表文件			存在截断文件，让文件内容为空。首先可以创建文件

```cpp
				int fd;

​				fd = open(“1.txt”,O_RDONLY|O_CREAT);//可以发现文件已经被创建
```

​				其次在1.txt中输入内容，利用ll命令可以发现1.txt文件大小不为0，更改程序					

```CPP
				fd = open(“1.txt”,O_RDONLY|O_CREAT|O_TRUNC,0644);//文件截断、清空,ll可以查看
```

##### 			2.open1.c

​					查看创建出的文件权限是否是 =mode &~umask,模式umask是0002，mode 设置成0777，利用ll查看			创建出的文件的实际权限

```cpp
				fd = open(“2.txt”,O_RDONLY|O_CREAT|O_TRUNC,0777);
```

​				实际权限为：	775。				777 &775=775,644&775=644

```
				-rwxrwxr-x 1 wenjx wenjx     0 10月 29 21:22 2.txt*
				-rw-r--r-- 1 wenjx wenjx     0 10月 29 21:06 1.txt
```

##### 3.open2.c

​					open常见错误和错误原因的测试，第一个错误是打开不存在的文件,提示 not a such file or dictionary；第二个错误是写方式打开只读文件，提示permission denied；第三个错误是写方式打开目录，提示* is a dictionary。三个错误分别对应test01(),test02(),test03();