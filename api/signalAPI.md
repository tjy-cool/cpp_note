# 信号signal机制分析

## 一、信号分类

## 二、信号安装

- signal
- sigaction

### 1. signal()

```c
#include <signal.h>
void (*signal(int signum, void(*handler(int))))(int);

// 上面的可以等价为：
typedef void (*sighandler_t)(int)
sighandler_t signal(int signum, sighandler_t handler);
```

## 三、信号发送

- kill()
- raise()
- sigqueue()
- alarm()
- settimer()
- abort()

### 3.1 kill()

```c
#include <sys/types.h>
#include <signal.h>
int kill(pid_t pid, int sig);
```

### 3.2 pause()

```c
#include <unistd.h>
int pause(void);
```

### 3.3 alarm()

```c
#include <unistd.h>
unsigned int alarm(unsigned int seconds);
```

### 3.4 setitimer()

```c
#include <sys/time.h>

int getitimer(int which, struct itimerval *value);

int setitimer(int which, const struct itimerval *value, struct itimerval *ovalue);

// itimerval结构体
struct itimerval {
    struct timeval it_interval; /* 下一次的取值 */
    struct timeval it_value; /* 本次的设定值 */

};

// timeval结构体
struct timeval {
    long tv_sec; /* 秒 */
    long tv_usec; /* 微秒，1秒 = 1000000 微秒*/
};
```

### 3.5 abort()

```c
#include <stdlib.h>
void abort(void);
```

### 3.6 raise()

```c
#include <signal.h>
int raise(int signo)
```

## 四、信号集及信号集操作函数

### 4.1 信号集的数据类型

信号集用来描述信号的集合，每个信号占用一位。Linux所支持的所有信号可以全部或部分的出现在信号集中，主要与信号阻塞相关函数配合使用。

```c
typedef struct {
unsigned long sig[_NSIG_WORDS]；
} sigset_t
```

### 4.2 信号集相关操作函数

```c
#include <signal.h>

// 初始化由set指定的信号集，信号集里面的所有信号被清空
int sigemptyset(sigset_t *set)；

// 调用该函数后，set指向的信号集中将包含linux支持的64种信号
int sigfillset(sigset_t *set)；

// 在set指向的信号集中加入signum信号
int sigaddset(sigset_t *set, int signum)

// 在set指向的信号集中删除signum信号
int sigdelset(sigset_t *set, int signum)；

// 判定信号signum是否在set指向的信号集中
int sigismember(const sigset_t *set, int signum)；
```

## 五、信号阻塞与信号未决

```c
#include <signal.h>

// 能够根据参数how来实现对信号集的操作
/*
SIG_BLOCK 在进程当前阻塞信号集中添加set指向信号集中的信号

SIG_UNBLOCK 如果进程阻塞信号集中包含set指向信号集中的信号，则解除对该信号的阻塞

SIG_SETMASK 更新进程阻塞信号集为set指向的信号集
*/
int  sigprocmask(int  how,  const  sigset_t *set, sigset_t *oldset))；

// 获得当前已递送到进程，却被阻塞的所有信号，在set指向的信号集中返回结果。
int sigpending(sigset_t *set));

// 在接收到某个信号之前, 临时用mask替换进程的信号掩码, 并暂停进程执行，直到收到信号为止。
int sigsuspend(const sigset_t *mask))；
```
