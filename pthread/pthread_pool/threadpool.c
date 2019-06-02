// 原文：https://blog.csdn.net/virgofarm/article/details/80994153 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "threadpool.h"

// 线程池中创建的线程执行函数体
void* thread_routine(void* args)
{
    struct timespec abstime;    // 时间结构体
    int timeout;
    threadpool_t *pool = (threadpool_t*)args;
    printf("thread %d is starting\n", (int)pthread_self());

    //死循环使线程池中空闲的线程可以复用
    while(1)
    {   
        timeout = 0;

        //访问线程池之前需要加锁
        condition_lock(&pool->ready);

        //空闲
        pool->idle++;

        //任务队列没有任务到来并且没有收到线程池销毁通知, 线程阻塞等待(进入这里面都是空闲线程，等待被唤醒)
        while(pool->first == NULL && !pool->quit)
        {   
            printf("thread %d is waiting\n", (int)pthread_self());

            //获取当前时间，并加上等待时间， 从而设置进程的超时睡眠时间
            clock_gettime(CLOCK_REALTIME, &abstime);  
            abstime.tv_sec += 2;
            int status;
            status = condition_timewait(&pool->ready, &abstime);  //该函数会解锁，允许其他线程访问，当被唤醒时，加锁
            if(status == ETIMEDOUT)
            {   
                printf("thread %d wait timed out\n", (int)pthread_self());
                timeout = 1;
                break;
            }   
        }   

        pool->idle--;
        if(pool->first != NULL)
        {   
            //取出任务队列最前的任务，移除任务，并执行任务
            task_t *t = pool->first;
            pool->first = t->next;
            //由于任务执行需要消耗时间，先解锁让其他线程访问线程池
            condition_unlock(&pool->ready);
            //执行任务
            t->run(t->args);
            //执行完任务释放内存
            free(t);
            //重新加锁
            condition_lock(&pool->ready);
        }   

        //退出线程池--销毁当前线程
        if(pool->quit && pool->first == NULL)
        {
            pool->counter--;//当前工作的线程数-1

            //若线程池中没有线程，唤醒等待线程（主线程--销毁线程池的线程）全部任务已经完成
            if(pool->counter == 0)
            {
                condition_signal(&pool->ready);
            }
            condition_unlock(&pool->ready);
            break;
        }
        //超时，说明线程没有任务可以执行, 跳出销毁线程
        if(timeout == 1)
        {
            pool->counter--;//当前工作的线程数-1
            condition_unlock(&pool->ready);
            break;
        }

        condition_unlock(&pool->ready);
    }

    printf("thread %d is exiting\n", (int)pthread_self());
    return NULL;
}

// 线程池初始化
void threadpool_init(threadpool_t* pool, int idle_threads, int max_threads)
{
    condition_init(&pool->ready);
    pool->first = NULL;
    pool->last  = NULL;
    pool->counter = 0;
    pool->idle = 0;
    pool->max_threads = max_threads;
    pool->quit = 0;

    int i = 0;
    for(int i = 0; i < idle_threads; ++i)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, thread_routine, pool);
        ++(pool->counter);
    }
}

// 往线程池中加入任务
int threadpool_add_task(threadpool_t* pool, void*(*run)(void* args), void* args)
{
    // 产生一个新的任务
    task_t* new_task = (task_t*)malloc(sizeof(task_t));
    new_task->run  = run;
    new_task->args = args;
    new_task->next = NULL;

    condition_lock(&pool->ready);
    if(NULL == pool->first)
    {
        pool->first = new_task;
    }
    else
    {
        pool->last->next = new_task;
    }
    pool->last = new_task;

    if(pool->idle > 0)
    {
        condition_signal(&pool->ready);
    }
    else if(pool->counter < pool->max_threads)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, thread_routine, args);
        pool->counter++;
    }
    else
    {
        condition_unlock(&pool->ready);
        return -1;
    }

    condition_unlock(&pool->ready);
    return 0;
}

// 摧毁线程池
void threadpool_destory(threadpool_t* pool)
{
    if(pool->quit)
    {
        return;
    }

    // 加锁
    condition_lock(&pool->ready);
    // 设置销毁标志为1
    pool->quit = 1;
    if(pool->counter > 0)
    {
        if(pool->idle > 0)
        {
            condition_broadcast(&pool->ready);
        }
        
        while(pool->counter)
        {
            condition_wait(&pool->ready);
        }
    }

    condition_unlock(&pool->ready);
    condition_destory(&pool->ready);
}