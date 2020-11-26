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

##### 7.pipe7.c

​				练习2：实现兄弟进程间通信，兄：ls 弟：wc-l，父进程回收子线程。这里的关键所在在于父进程必须要关闭关闭的写端，否则数据在管道中不能单项流动，就不能实现进程回收，观察不到现象

#### 2.fifo文件夹

##### 	1.fifo1.c

​			命名管道的创建和原理，通过mkfifo("myfifo",0644)执行后，然后ls发现有myfifo的管道文件

##### 	2.fiforw.c

​			在fifo1.c的基础上实现简单的命名管道通信

##### 	3.fifo2r.c  / fofo2w.c

​			分为两个文件，一个文件写管道，一个文件读管道.观察下面的现象：一个读端，多个写端，然后一个写端，多个读端

#### 	3.mmap文件夹

##### 		1.mmap.c

​				利用mmap创建映射区，因为映射的是文件，首先应该新建个文件，但是映射的大小要小于等于文件大小，新文件的大小是0，因此我们需要用ftruncate扩展下文件的大小，并且利用lseek(fd,0,SEEK_END)获得文件大小len,将len作为创建映射区的长度，映射区创建成功后我们得到指针p,可以利用strcpy写入p,也可以利用printf("%s",p)直接读取文件内容（写和读不需要借助read/write。最后利用munmap(p,len)来释放指针空间。

##### 2.mmap2.c

​			常见的mmap的注意事项和测试mmap的错误

##### 3.mmap3.c

​			其他参数满足的情况下，如果创建映射区时的映射区访问权限为私有，创建映射区不会出现错误，但是对映射区指针的修改只会对内存有效，不会反映到磁盘上

##### 4.mmap4.c

​			父子进程间mmap通信，首先先打开文件建立映射区，确认映射区建设成功以后，fork子进程。有下面几个知识点的回顾和学习。

​	1.首先有个全局变量var=100,在子进程var+=100,父进程不操作，分别输出var，可以看到父子进程输出结果分别是200,100

​	2.对于

`p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);`

返回值void*型指针，分别在父子进程中打印*p=%d，可以发现父子进程的输出结果一致。但是如果把MAP_SHARED改成MAP_PRIVATE，发现父进程的*p变成0了

##### 5.mmap5.c

​		如果创建映射区的时候

```cpp
p = (int*)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
```

这边可以输出下*p,发现是0,然后这个p我们在子进程修改指针p的大小，*p+=10,然后在父子进程中分别输出*p的大小，发现子进程是10，父进程还是0.这就意味着我们没有实现共享。只要改成MAP_SHARED，父子进程的输出都是10

##### 6.mmap6_r.c&mmap6_w.c

​			映射区实现非血缘关系的两个进程间通信。

​			mmap6_w.c:

​				首先是写端，建立映射区，这边建立映射区的大小是一个结构体的大小

```cpp
 23 struct Student
 24 {
 25     int id;
 26     char name[256];
 27     int age;
 28 };
```

```cpp
p = mmap(NULL,sizeof(stu),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)		
```

这样利用memcpy将结构体student的内容放到指针p中，这样指针p可以修改id，不断修改id

​		mmap6_r.c：

​			在读端建立映射区是相同的，然后不断读取指针p的内容，可以看到在写进程更改的内容，在读进程能够读取到

##### 7.mmap7.c

​		建立匿名映射区，不再需要打开文件了

### 5.signals文件夹

#### 	1.killtest.c

​		利用 killstatus =  kill(getppid(),SIGKILL);给进程发送SIGKILL信号，返回值0代表成功发送信号。观察现象。可以发现程序执行后输出killed后结束,因为SIGKILL的作用

#### 	 2.killtest2.c

​		发送信号改成 killstatus =  kill(getppid(),SIGFPE)，观察输出现象。和上面的几乎一样，唯一区别是输出“Floating point exception (core dumped)”结束，因为SIGFPE的作用

#### 		3.killpractice.c

​		循环创建5个子进程，父进程用kill函数终止任一子进程。还是利用下标来判断是父进程还是子进程，父进程的下标i=5,然后pid=fork(),kill函数放在父进程中  int status = kill(pid,SIGKILL);

父进程的pid一定是子进程的id,所以能够杀死一个子进程

#### 		4.alarm.c

​		定义变量i=0，alarm(1)查看1秒钟内电脑进行多少次运算，i++,输出i,1秒到了后程序结束，输出alarm clock，可以发现运行不到2000次。

​		time ./alarm 可以在运行程序时计算程序运行的系统时间，用户时间，实际时间，等待时间

​		time ./alarm >out将之前printf的结果输出到out文件中，结果一秒钟运行了接近800万次，可见io输出是很浪费时间的。

#### 		5.setitimer.c

​		程序的主要功能和alarm.c一样，也是查看每秒钟电脑进行多少次运行。setitimer比alarm多了很多参数，可以实现周期定时，配置也复杂一点。it_interval是间隔时间，it_value是定时时间

```c
 23 struct itimerval new_t;
 24 struct itimerval old_t;
 25
 26 new_t.it_interval.tv_sec = 0;
 27 new_t.it_interval.tv_usec = 0;
 28 new_t.it_value.tv_sec = 1;
 29 new_t.it_value.tv_usec = 0;
 30
 31 old_t.it_interval.tv_sec = 0;
 32 old_t.it_interval.tv_usec = 0;
 33 old_t.it_value.tv_sec = 0;
 34 old_t.it_value.tv_usec = 0;
 35
 36 setitimer(ITIMER_REAL,&new_t,&old_t);
```

#### 		6.sigopera文件夹：和信号操作有关

##### 				1.sigtest.c

​					测试屏蔽信号SIGINT，正常一个程序执行时，按ctrl+c会程序停止。流程如下：

```
 36     sigset_t set,oldset,pedset;
 37     int ret=0;
 38     sigemptyset(&set);
 39     sigaddset(&set,SIGINT);
 41     ret = sigprocmask(SIG_BLOCK,&set,&oldset);
```

​	第一步定义sigset_t类型的变量，第二步清空，利用sigemptyset，第三步添加信号屏蔽字，sigaddset(&set,SIGINT),第四步用自己的set替换mask，利用sigprocmask函数，其中宏SIG_BLOCK是设置阻塞的意思。

​	我们的程序可以用死循环来验证，无法用ctrl+c中断程序。也可以利用  ret = sigpending(&pedset);来查看2号信号SIGINT的未决信号集位图是否为1.执行程序时，可以发现在没有任何按键的时候，程序输出32个0，当按下ctrl+c时，2号变为1，证明了信号的确被屏蔽了。

​	同时可以屏蔽多个信号，我们sigaddset(&set,SIGKILL),在执行程序，发现ctrl+z依旧可以终止程序，验证了SIGKILL不可被屏蔽。

##### 			2.sigcatch.c

​			利用signal函数来注册信号的捕捉，可以查看函数原型

```c
 #include <signal.h>
 typedef void (*sighandler_t)(int);
 sighandler_t signal(int signum, sighandler_t handler);
```

​	sighandler_t是一个函数指针类型，参数1是信号编号，信号2是一个回调函数，回调函数必须返回值void,参数为int型变量。

​	 signal(SIGINT,sig_catch);就是注册了2号信号的捕捉函数为sig_catch，可以发现程序执行时，我们按下ctrl+c，内核会去调用sig_catch函数。

​		因为signal在不同版本linux含义不同，所以信号的捕捉应该用sigaction函数。

##### 3.sigactioncatch.c

​	利用sigaction函数完成注册信号的捕捉

```c
 #include <signal.h>
 int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact);
```
```c
 struct sigaction {
 void     (*sa_handler)(int);
 void     (*sa_sigaction)(int, siginfo_t *, void *);
 sigset_t   sa_mask;
 int        sa_flags;
 void     (*sa_restorer)(void);
       };
```
sigaction函数参数1是注册信号，参数2和3是两个结构体参数，使用标准方法：

```c
 27     struct sigaction act,oldact;
 28     //结构体的赋值
 29     act.sa_handler=sig_catch;
 30     sigemptyset(&(act.sa_mask));//只在捕捉函数时有效
 31     act.sa_flags =0;
 35     ret  = sigaction(SIGINT,&act,&oldact);//注册信号捕捉函数
```

sa_flags默认设置0，屏蔽2号信号执行函数时，再来2号信号时默认屏蔽。

##### 4.sigactioncatch2.c

​	在sigactioncatch.c的基础上，我们注册了SIGINT信号的捕捉函数，在这期间，我们也可以同时设置其他信号的屏蔽，利用:

 sigaddset(&act.sa_mask,SIGQUIT);//设置屏蔽 

可以发现SIGQUIT信号也没有用了。注意在设置信号捕捉期间，是用sa_mask替代mask,mask生命周期是程序创建到程序结束。所以这个实际上验证了sa_mask在捕捉函数执行期间的屏蔽作用。

##### 5.catchchild.c

​	SIGCHLD信号是子进程的状态发生变化，子进程就会发出这个信号，可以利用这个信号回收子进程。循环创建5个子进程，在i==5的时候，是父进程，然后父进程设置如下：

```c
 43         struct sigaction act,oldact;
 44         act.sa_handler=catch_Child;
 45         sigemptyset(&(act.sa_mask));
 46         act.sa_flags=0;
 47         //sigaction(SIGCHLD,&act,&oldact);
 48         sigaction(SIGCHLD,&act,NULL);
```

注意oldact含义是代表原来对信号的处理方式，我们可以传NULL，或者只是定义struct sigaction oldact，然后传过去就行。这个版本在父进程中while(1);然后子进程中设置了sleep(5)；如果是父进程先执行，那么父进程注册了捕捉后，就阻塞等待，子进程之所以要sleep（5）的原因是，有可能子进程先执行，此时父进程还尚未注册，那么子进程结束后可能没有回收成为僵尸进程，有sleep(5)可以确保父进程先执行，子进程后执行，避免僵尸进程。但是阻塞在这sleep(5)会造成程序卡顿缓慢。

##### 6.catchchild2.c

​	上面的catchchild.c sleep可以解决僵尸进程问题，但是有弊端，我们可以利用循环回收来解决，不用睡眠。代码如下：

```
 27     while(( wpid = wait(&status))!=-1) {
 28         if (WIFEXITED(status)) {
 29             printf("-------------seesee-------:catch child：%d,retvalue=%d,\n",wpid,WEXITSTATUS(status));
 30         }
 31     }
```

wait回收失败返回-1这样可以进行循环回收。然后这边子进程没有sleep.

##### 	7.catchchild3.c

​		之前的程序父进程while(1)阻塞，虽然子进程的僵尸进程问题解决了，但是由于父进程只能用ctrl+z终止，这样就会导致父进程出现僵尸进程。解决方法是在父进程注册SIGCHLD信号捕捉前，先屏蔽SIGCHLD信号；

```c
 43     sigset_t set;
 44     sigemptyset(&set);
 45     sigaddset(&set,SIGCHLD);
 46     sigprocmask(SIG_BLOCK,&set,NULL);
```

然后在注册信号捕捉函数之后，解除屏蔽：

​	sigprocmask(SIG_UNBLOCK,&set,NULL);

这样父进程不用while(1)；阻塞，子进程也不用睡眠

#### 7.dameo.c

​	守护进程创建。首先创建进程，pid=fork(),对于父进程肯定pid>0,所以对于父进程无法创建守护进程，直接exit(0)结束。

​		然后子线程第二步创建新会话，pid=setsid()函数，使得子进程完全独立出来，脱离控制。

​		第三步，改变当前工作目录，这一步不是必须的，chdir到新目录

​		第四步，重设文件权限掩码，之所以做这一步是为了提升守护进程的灵活性，这样守护进程使用文件就比较方便，不担心有权限问题

​		第五步。关闭不需要的文件描述符，因为守护进程不存在终端，无法交互，那么显示终端的文件描述符0，1，2（也就是输入，输出，报错）就没有存在的价值，所以应该关闭这些文件描述符。但是另一方面，在正常情况下我们open文件的返回值文件描述符是从3开始的，如果你关闭0，1，2的话，再open文件的返回值是从0开始，不太符合编程习惯，因此可以讲0，1，2重定向到/dev/null那边。

​		第六步：守护进程是后台服务进程，一直在运行的，所以我们用while(1);来模拟这种状态。

### 7.pthread文件夹

#### 		1.create_pth.c

​			pthread_create（&tid,NULL,回调函数，回调函数参数）尝试创建线程，并且在子线程中输出一句话，实际运行发现子线程没有进行。原因是线程创建完毕后主进程就return 0结束了，子线程完全没有执行的机会。

#### 		2.create_pth2.c

​			在create_pth.c的基础上，创建线程后，进行sleep(1)这样不至于刚创建线程完毕就执行return 0,给子线程运行的机会，发现子线程正常运行了

#### 		3.create_pth3.c

​			循环创建5个子线程，我自己最开始写的版本，虽然创建成功，输出的结果也是正常的，实际上是有漏洞的。

```c
 34     for(int i=0;i<5;i++) {
 35         ret =  pthread_create(&tid,NULL,tfn,&i);//去执行函数
 36         if (ret!=0)
 37             geterror("create error");
 38 
 39        sleep(1);
 40     }

```

 `printf("thread %d:pid=%d,tid=%lu,\n",*(int*)arg,getpid(),pthread_self());``

问题就在于我这边传的是地址，传完地址到子线程输出的时候，因为每创建一个线程，就sleep(1),所以这时候通过地址去读i，还是可以读到结果的。

#### 		4.create_pth4.c

​			教程里给的标准版本，没有漏洞的版本。

```c
 34     for(int i=0;i<5;i++) {
 35         ret =  pthread_create(&tid,NULL,tfn,(void*)i);//去执行函数
 36         if (ret!=0)
 37             geterror("create error");
 38       // sleep(1);这个sleep(1)放在这边还是放在下面都是可以正常输出
 39 
 40     }  
//子线程输出语句
25  printf("thread %d:pid=%d,tid=%lu,\n",(int)arg,getpid(),pthread_self());


```

区别在于这边是直接传的值，而不是地址，这样，即使创建线程结束后没有sleep，即便在子线程还没有执行到i就发生变化，也不影响。

#### 		5.create_pth5.c

​		错误演示版本。

```c
 35     for(int i=0;i<5;i++) {
 36         ret =  pthread_create(&tid,NULL,tfn,&i);//去执行函数
 37         if (ret!=0)
 38             geterror("create error");
 39 
 40     }
     printf("thread %d:pid=%d,tid=%lu,\n",*(int*)arg,getpid(),pthread_self());

```

传的是指针，然后也没有睡眠，当子进程还尚未执行的时候，i的值已经变动，所以输出的结果不是传值的那个结果。

#### 		6.thread_share.c

​		 验证线程共享全局变量

#### 		7.pth_exit.c

​		想要在create_pth4.c的基础上，如果i==2的话，就exit(0)结束，按照设想thread3就不会输出，会打印thread1,2,4,5。但是实际运行显示的1，2等。原因就是exit(0)执行会导致整个进程退出。然后注释exit(0),改成return NULL,就会打印thread1,2,4,5.说明return NULL会导致线程退出。不过线程在回调函数中，即便是普通函数也会让函数结束。

```c
 26     if (i==2) {
 27         //exit(0);//效果不好，整个进程都退出了
 28         return NULL;
 29     }

```

#### 8.pth_exit2.c

​		把return NULL写到函数func()中，然后i==2时调用func(),其他逻辑和pth_exit.c相同，不能实现预想的功能，而是打印的是thread1，2，3，4，5.原因是因为return 语句并不是退出，而是返回到调用者那里去。

```c
 23 void* func(void) {
 24
 25     return NULL;
 26 }
```

```c
 30     if (i==2) {
 31         //exit(0);//效果不好，整个进程都退出了
 32         // return NULL;
 33         func();
 34     }
```

在func()中return ,那么就会回到if语句这边，线程接着执行下面的打印语句。

#### 9.pth_exit3.c

​		利用pthread_exit函数来退出线程，不管是和pth_exit.c一样放在if语句中，还是和pth_exit2.c一样在if语句中调用func()函数，在func函数里执行pthread_exit(),都可以实现线程退出。因为pthread_exit()函数的作用就是退出当前线程。

#### 10.pth_join.c

​		pthread_join函数阻塞回收线程的使用示例，首先是创建线程，我们的线程里有一个结构体，如下：

```c
 22 struct thrd {
 23     int var;
 24     char str[256];
 25 };
```

线程的作用就是定义一个结构体指针，赋值后返回，注意线程回调函数返回值void *类型，所以返回值是

​	   `return (void*)tval;`

然后利用pthread_join来回收，有两个参数，参数1就是线程id,参数2是一个2级指针类型，参数2是存储子线程的退出值的。回收过程如下

```c
  struct thrd *retval;
  ret = pthread_join(tid,(void**)&retval);
```

然后返回值ret==0的话，证明回收成功，我们就可以读取这个retval的值，输出如下：

printf("child thread with var=%d,str=%s\n",retval->var,retval->str);

当然最后可以释放一下这个结构体指针。

#### 11.pth_join2.c

​		整体逻辑和pth_join.c相似，子进程代码如下：

```c
 23 void * tfn(void * arg) {
 24     int a=10;
 25     return (void*)&a;
 26 }
```

然后用pthread_join阻塞回收，并读取线程的退出值，代码如下：

```c
 int *val;
 ret = pthread_join(tid,(void**)&val);
```

按照正常来说，只要是ret==0,pthread_join执行是正常的，那么我们可以输出下返回值：

 printf("child thread with val=%d\n",*val);

运行这段代码，发现出现段错误，写入core文件。错误的原因是因为a是局部变量，存储在用户栈中，当子线程执行结束后栈空间释放，利用a的地址找不到a了，然后下面pthread_join的val也就是空了，尝试去解引用空指针，会出现段错误。利用下面的代码验证了：

```c
 37     if (val==NULL) {//尝试返回局部变量地址，这个val是空，自然解引用错误
 38         printf("val is null pointer\n");
 39     }
 40     else {
 41         printf("val is not null pointer\n");
 42         printf("child thread with val=%d\n",*val);
 43
 44     }
```

输出了val is null pointer。

#### 12.pth_join3.c

​		比较pth_join.c和pth_join2.c发现不应该返回局部变量地址，而是应该返回指针，因此其它逻辑不变，修改子进程代码如下：

```c
 23 void * tfn(void * arg) {
 24     //int *a=(int*)malloc(sizeof(int));//正确方式
 25     int *a=NULL;//错误方式，没有开辟内存
 26     *a=10;
 27     return (void*)a;
 28 }
```

同样会出现段错误，原因很简单，指针没有开辟内存空间就使用*a,向未知内存空间赋值，肯定不允许。正确的方式应该先开辟空间，即24行的代码，然后其他逻辑不变，发现可以成功输出。

#### 13.pth_join4.c

​		要知道pth_join2.c出问题的根本原因是局部变量a 返回后，线程执行完毕，再去访问a地址的内存空间就是非法操作了。代码类比pth_join.c，首先还是结构体操作，子线程不开辟内存空间，而是由线程变量赋值，如下：

```c
 28 void * tfn(void * arg) {
 29     struct thrd *tval=(struct thrd*) arg;//不初始化，直接传参
 30     tval->var=100;
 31     strcpy(tval->str,"hello,thread");
 32
 33     return (void*)tval;
 34 }
```

再创建线程时，传递局部变量做为参数，如下：

```c
   struct thrd arg;
   int ret = pthread_create(&tid,NULL,tfn,(void*)&arg);
```

然后下面回收和之前一样，发现可以成功输出结构体的值。原因是arg作为参数传递，它是定义在主线程的，即便是子线程执行完毕了，主线程还没有结束，自然arg的地址空间就还在，所以不会出错。

#### 14.pth_recy.c

​	 		练习，循环创建多个线程，并利用pthread_join回收。因为pthread_join回收的参数是线程号，所以新建一个数组来存储线程号，并利用for循环创建线程和回收线程，代码如下：

```c
 pthread_t tid[5];
 for(int i=0;i<5;i++) {
 	ret = pthread_create(&tid[i],NULL,tfn,(void*)i);
 	//...其它代码...
 	ret = pthread_join(tid[i],(void**)&retval);
 }
 
```

#### 15.pth_cal.c

​		了解pthread_cancel杀死进程。

#### 16.pth_detach.c/pth_detach1.c/pth_detach2.c

​			pthread_detach函数实现线程分离。线程处于detach状态后就不能利用join进行回收了，会返回ERROR IN VALUE错误（EINVAL）。测试代码如下：

```C
 38     ret=pthread_detach(tid);//设置线程分离
 39     if (ret!=0)
 40         geterror("detach error");
```

分离成功返回0，否则返回的就是错误号。然后我们利用线程回收：

```c
ret =  pthread_join(tid,NULL);
if (ret!=0) {
 printf("second,join ret = %d,errno=%d\n",ret,errno);
 geterror("join errno");
}

```

发现输出的ret是22，说明join没有成功，但是输出的是

join error:Success，显得十分别扭。这个原因是因为perror是通过errno显示错误的，但是我们刚刚join错误，errno还是0，并没有设置成其他值，所以在线程中perror失效，因为pthread_join()错误直接返回错误号22，我们应该用strerror(ret)来查看问题所在。

   fprintf(stderr,"join ret errno=%s\n",strerror(ret));

可以看到输出为：join ret errno=Invalid argument

无效的参数错误，对于pthread_join,参数tid因为是detached的线程，因此无效。

此外，我们在线程中判断错误的方式应该改成直接输出错误号，如下所示。

```c
 36     if (ret!=0){
 37         fprintf(stderr,"create errno=%s\n",strerror(ret));
 38         exit(1);
 39     }
```

#### 17.pth_creat_detach.c/pth_creat_detach1.c

​		分离态的线程不会产生僵尸线程。我们可以利用pthread_detach使得线程分离，但是假如有几十个线程，我们就需要有几十个pthread_detach()调用，这不合理，可以在线程创建的时候就使得线程是分离态。原理是修改pthread_create的参数2，是线程属性，之前我们一直传的是NULL。创建的步骤如下：

```c
pthread_attr_t attr;//创建线程的属性
ret  = pthread_attr_init(&attr);//初始化线程属性
//错误判断
ret=pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//设置线程属性为detached
//错误判断
ret =  pthread_create(&tid,&attr,tfn,NULL);//去创建线程
//错误判断
ret = pthread_attr_destroy(&attr);//销毁线程属性所占用的资源
//错误判断

```

为了验证我们创建的线程是否是分离态，我们可以采取两种方法去判断，第一种方式就是利用join不能用于回收分离态线程（pth_creat_detach.c),会报无效参数错误，方法2就是利用pthread_attr_getdetachstate来判断。

方式1代码：

```c
 49     ret =  pthread_join(tid,NULL);
 50     if (ret!=0){
 51         fprintf(stderr,"join errno =%s\n",strerror(ret));
 52         exit(1);
 53     }
```

方式2代码：

```c
 int status;
 ret = pthread_attr_getdetachstate(&attr,&status);
 //错误判断
 if (status==PTHREAD_CREATE_DETACHED) {
     printf("pth_cre_deta success\n");
 }
```

### 8.pthread/pth_mutex文件夹

在pthread文件夹下的pth_mutex文件夹内容。

#### 	1.printTest.c

​			创建一次子进程，然后子进程中while循环输出hello（不换行），world（换行），父进程循环输出HELLO（不换行）,WORLD（换行）,实际测试不能如愿。有时候会出现两种输出在一排的现象，原因是主子线程存在竞争。

#### 	2.printTestMutex.c

​			利用互斥锁来尝试解决。我加锁的主子线程代码如下所示。

子线程：

```c
 21 void * tfn(void *arg) {
 22     srand(time(NULL));
 23     while (1) {
 24         pthread_mutex_lock(&mutex);
 25         printf("hello");
 26         sleep(rand()%3);
 27         printf(",world!\n");
 28         sleep(rand()%3);
 29         pthread_mutex_unlock(&mutex);
 30     }
 31     return NULL;
 32
 33 }
```

主线程：

```c
 49     while (1) {
 50         pthread_mutex_lock(&mutex);
 51         printf("HELLO");
 52         sleep(rand()%3);
 53         printf(",WORLD!\n");
 54         sleep(rand()%3);
 55         pthread_mutex_unlock(&mutex);
 56
 57     }
```

虽然我这边有主动上锁，但是还是没有用。我还尝试把加锁和解锁放在while循环的外面，还是无法实现功能。输出几乎全部都是HELLO,WORLD（后面证实，如果把sleep时间缩短，可以看到hello,world）

#### 3.printTestMutex1.c

这个是符合要求的版本，和上面的唯一区别就是加锁和解锁的位置不同，以子线程为例：

```c
 22     while (1) {
 23         pthread_mutex_lock(&mutex);
 24         printf("hello");
 25         sleep(rand()%3);
 26         printf(",world!\n");
 27         pthread_mutex_unlock(&mutex);
 28         sleep(2);
 29     }
```

关键区别在于解锁后又睡眠，而上面是睡眠后解锁。我们说锁的使用要保证粒度，即访问共享数据结束后，就解锁，而printTestMutex.c访问共享数据结束后没有及时解锁，这是一种错误用法。程序一开始，主线程先获得锁，子线程因此阻塞，当主线程执行到睡眠-解锁结束后，程序运行可能是

1.主线程继续进行while循环，主线程继续获得锁

2.子线程结束阻塞获得锁，主线程阻塞

cpu调度是随机的，主子线程的竞争是必然的。而正确版本在主线程执行到解锁时，主线程睡眠了，在主线程解锁前，子线程一直阻塞在锁这边，那么主线程解锁，程序运行结果为

1.主线程执行睡眠

2.子线程结束阻塞，获得锁

这两个事件互相不关联，所以能够同时进行，所以能够实现同步。

#### 4.printTestMutex2.c

​		在printTestMutex.c的基础上，我们可以看到printTestMutex.c执行大部分都是HELLO,WORLD，因为程序有睡眠较长，错误认为只有主线程在执行，实际上主子线程的竞争子线程也是能获得资源的，把睡眠时间改短一点，例如rand()%1,输出的时候，连续好多个大写的HELLO,WORLD，然后又连续很多个hello,world,目测可能hello，world的数量要少一点。这说明子线程并非完全没有执行机会。

#### 5.deadmutex.c

​		死锁的情况1.对一个线程加锁两次。第一次加锁，线程有访问公共区域的权限，换言之是程序能执行加锁下面的程序，而其他锁只能在阻塞状态。然后程序再次对该线程加锁，第二次阻塞在锁这这边一直到解锁，但是第一次加锁也是该线程，因此无法解锁，一直阻塞。

#### 6.deadmutex2.c

​		死锁的情况2：线程a拥有加锁1，线程b加锁2，然后线程a想要加锁2，线程b想要加锁1。线程a想要加锁2 就得线程b解锁，而线程b加锁1就得线程a解锁，因而出现死锁。

#### 7.rwlock.c

​		读写锁程序测试。创建8个线程，其中3个线程写，5个线程读，利用读写锁来共同操作同一个数据。在写线程，利用写锁，

 pthread_rwlock_wrlock(&rwlock);

在读线程，利用读锁

pthread_rwlock_rdlock(&rwlock);

#### 8.proc_consumer.c

​		利用条件变量写的生产者，消费者模型。主线程依次创建两个线程，分为生产者线程和消费者线程。

首先全局里初始化锁mutex和条件变量has_product，然后这边的产品是个链表类型的变量：

```c
 19 struct msg {
 21     struct  msg* next;
 22     int num;
 24 };
 25 struct msg *head;//产品
 27 pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
 28 pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;//静态初始化
```

生产者生产：

```c
 30     while(1) {
 31         struct msg *mp=malloc(sizeof(struct msg));
 32         mp->num=rand()%1000;//模拟生产数据
 33         printf("---proc,mp->num=%d\n",mp->num);
 34         pthread_mutex_lock(&mutex);//加锁
 35         mp->next=head;//写公共区域操作
 36         head=mp;
 37         pthread_mutex_unlock(&mutex);//解锁
 38         pthread_cond_signal(&has_product);//唤醒阻塞再条件变量 has_data上的变量
 39         sleep(rand()%3);
 40     }
```

对于产品变量head,生产就是给定值。生产者代码首先定义结构体变量mp,更新num数据，然后加锁。在锁内将head更新为mp,然后解锁。

再利用pthread_cond_signal来通知阻塞在条件变量has_product的线程。

消费者消费代码：

```c
 45     while(1) {
 46         struct msg *mp;
 47         pthread_mutex_lock(&mutex);//加锁
 48         if (head==NULL) //空的时候才判断不为空直接消费
 49          pthread_cond_wait(&has_product,&mutex);//阻塞等待条件变量,解锁
 51         mp=head;//当pthread_cond_wait返回时，会重新加锁
 52         head=mp->next;
 53         pthread_mutex_unlock(&mutex);
 54         printf("====================---consumer,mp->num=%d\n",mp->num);
 55         free(mp);
 56         sleep(rand()%3);}
 57     return NULL;
 58 }
```

首先也是定义一个没有开辟内存空间的结构体变量mp,然后加锁。两种可能的情况。

1.这时候生产者正在执行锁内代码，那么这边阻塞

2.生产者已经解锁，这边继续执行

假如这边继续执行，那么生产者那边被阻塞，并且发现head仍然为空，意味着生产者还没有生产产品，无法消费，因此需要阻塞等待。即

pthread_cond_wait(&has_product,&mutex);

首先这边阻塞等待条件变量cond,然后解锁mutex,这样生产者那边可以结束阻塞，进行生产，等待生产完毕时利用

pthread_cond_signal()唤醒阻塞在线程上的消费者线程，这样消费者线程解除阻塞，重新上锁，

消费者消费产品时候，生产者因为锁阻塞无法生产。

#### 9.proc_consumer2.c

​			一个生产者，多个消费者的情况。

生产者的代码都是相同的，消费者的代码有些变动。

```c
 44     while(1) {
 45         struct msg *mp;
 46         pthread_mutex_lock(&mutex);//加锁
 47         while(head==NULL) //多个消费者时，要从if 改为while
 48             pthread_cond_wait(&has_product,&mutex);//阻塞等待条件变量,解锁
 49         //当pthread_cond_waitw返回时，会重新加锁
 50         mp=head;
 51         head=mp->next;
 52         pthread_mutex_unlock(&mutex);
 53         printf("====================---consumer:%lu,mp->num=%d\n",pthread_self(),mp->num);
 54         free(mp);
 55         sleep(rand()%3);}
```

假如仍然为if.消费者A加锁后，消费者B和生产者阻塞,head为空满足，A线程循环阻塞在条件变量上，会解锁。

这时候假如消费者B获得锁，head为空满足，B线程循环阻塞在条件变量上，会解锁。

这时候生产者结束阻塞，写head,然后解锁，pthread_cond_signal通知阻塞在条件变量的线程（至少通知1个，应该是全部通知）。A,B线程都结束阻塞，假如A获得了，因为是if,因此下面就进行消费，然后

把head的内容读取到再置空，然后B线程也获得了，然后对已经为空的head进行->next操作，显然会出错。所以正确的方法把if改成while,当两个线程结束条件变量阻塞，是否进行消费还取决于head是否为空，如果head为空，可能是被别的消费者消费了，仍然需要进行条件变量阻塞。

#### 10.proc_consumer3.c

​		通过这个程序，主线程创建多线程可以重复利用tid,tid是和线程内部的pthread_self（）对应的。也就是如下的代码创建了两个线程：

```c
pthread_t tid[2];
ret = pthread_create(&tid[0],NULL,producer,NULL);
ret=pthread_create(&tid[1],NULL,consumer,NULL);
ret=pthread_create(&tid[1],NULL,consumer,NULL);
```

第三行，第四行用的tid都是tid[1],但是创建的线程并不是同一个，我在proc_consumer3.c中把数组大小改成3，利用不同的tid创建线程，完全不影响程序结果。

#### 11.proc_consumer4.c

​		在proc_consumer2.c中，多个消费者情况要改成while(head==NULL),原因已经解释了，这边多个消费者然后仍然是if(head==NULL),查看运行结果，我们可以发现开始正常执行，过了一会出现段错误。

#### 12.proc_consumer_sem.c

​			定义两个信号量proc ,consu，分别用于生产者，和消费者，在主线程中利用sem_init初始化。然后分别创建produce和consume线程。

​	对于生产者，利用sem_wait（&proc)后，模拟生产过程，在生产完毕后，利用sem_post(&consu)通知阻塞在信号量consu上的消费者线程。

​	而对于消费者，利用sem_wait(&consu)模拟消费过程，在消费完，利用sem_post(&proc)通知阻塞在信号量proc的生产和线程。



### 6.linuxsystem文件夹--前面linux系统基础知识

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

#### 2.makefile文件夹

​		一些 关于makefile编写规则的文件夹和测试c文件，最重要的文件就是Makefile

#### 3.io_rw文件夹

##### 	1.tinycp.c

​			利用read\write函数实现cp的简单功能，注意cp的目标文件的打开要指明0644权限，不然会出现空文件和访问拒绝现象

