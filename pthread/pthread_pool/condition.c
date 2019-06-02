#include "condition.h"

// 初始化
int condition_init(condition_t* cond)
{
    int status = 0;
    do{
        if (0 != (status = pthread_mutex_init(&cond->pmutex, NULL)))
        {
            break;
        }
        if (0 != (status = pthread_cond_init(&cond->pcond, NULL)))
        {
            break;
        }
    }while(0);

    return status;
}

// 互斥加锁
int condition_lock(condition_t* cond)
{
    return pthread_mutex_lock(&cond->pmutex);
}

// 互斥解锁
int condition_unlock(condition_t* cond)
{
    return pthread_mutex_unlock(&cond->pmutex);
}

// 同步等待
int condition_wait(condition_t* cond)
{
    return pthread_cond_wait(&cond->pcond, &cond->pmutex);
}

int condition_timewait(condition_t* cond, const struct timespec* abstime)
{
    return pthread_cond_timedwait(&cond->pcond, &cond->pmutex, abstime);
}

int condition_signal(condition_t* cond)
{
    return pthread_cond_signal(&cond->pcond);
}

int condition_broadcast(condition_t* cond)
{
    return pthread_cond_broadcast(&cond->pcond);
}

int condition_destory(condition_t* cond)
{
    int status = 0;
    do
    {
        if(0 != (status = pthread_mutex_destroy(&cond->pmutex)))
        {
            break;
        }
        if(0 != (status = pthread_cond_destroy(&cond->pcond)))
        {
            break;
        }
    } while (0);
    
    return status;
}