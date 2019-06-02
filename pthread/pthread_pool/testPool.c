#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "threadpool.h"

void* mytask(void* args)
{
    printf("thread %d is working on task %d\n", (int)pthread_self(),(int)args);
    sleep(1);
    return NULL;
}

int main(void)
{
    threadpool_t mypool;
    threadpool_init(&mypool, 3, 5);
    for(int i = 0; i < 10; ++i)
    {
        threadpool_add_task(&mypool, mytask, (void*)&i);
    }
    threadpool_destory(&mypool);
    return 0;
}