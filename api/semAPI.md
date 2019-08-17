# 信号量

## 相关操作函数

```c
// 头文件
#include <semaphore.h>

/*
sem ：指向信号量对象
pshared : 指明信号量的类型。不为0时此信号量在进程间共享，否则只能为当前进程的所有线程共享。
value : 指定信号量值的大小 
*/
int sem_init(sem_t *sem, int pshared, unsigned int value);

// 其中sem是要销毁的信号量。只有用sem_init初始化的信号量才能用sem_destroy销毁。
int sem_destroy(sem_t *sem);

// 相当于P操作。等待信号量，如果信号量的值大于0,将信号量的值减1,立即返回。如果信号量的值为0,则线程阻塞。成功返回0,失败返回-1。
int sem_wait(sem_t *sem);

// 相当于V操作。释放信号量，让信号量的值加1。
int sem_post(sem_t *sem);
```

## 使用实例

```c
// 原文：https://blog.csdn.net/Dancer__Sky/article/details/71101808 
#include <stdint.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

sem_t sem;

void *testfunc(void *arg)
{
    while(1)
    {
        sem_wait(&sem);
        //do something....
        printf("hello world...\n");
    }
}

int main()
{
    pthread_t ps;
    sem_init(&sem, 0, 0);
    pthread_create(&ps,NULL,testfunc,NULL);
    while(1)
    {
        //每隔一秒sem_post 信号量sem加1 子线程sem_wait解除等待 打印hello world
        sem_post(&sem);
        sleep(1);
    }
    return 0;
}
```
