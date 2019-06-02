#ifndef __THREAD_POOL_H_
#define __THREAD_POOL_H_

#include "condition.h"

typedef struct __task
{
    void* (*run)(void* args);   // 线程运行函数，需要执行的任务
    void* args;                 // 线程参数
    struct __task* next;        // 任务队列中的下一个任务 
}task_t;


typedef struct __threadpool
{
    condition_t ready;   // 状态量
    task_t* first;
    task_t* last;
    int counter;
    int idle;
    int max_threads;
    int quit;
}threadpool_t;

// 线程池初始化
void threadpool_init(threadpool_t* pool, int idle_threads, int max_threads);

// 往线程池中加入任务
int threadpool_add_task(threadpool_t* pool, void*(*run)(void* args), void* args);

// 摧毁线程池
void threadpool_destory(threadpool_t* pool);

#endif
