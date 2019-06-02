#ifndef __CONDITION_H_
#define __CONDITION_H_

#include <pthread.h>

// 封装互斥变量和条件变量作为状态
typedef struct condition
{
    pthread_mutex_t pmutex;
    pthread_cond_t  pcond;
}condition_t;

// 对状态的操作函数
int condition_init(condition_t* cond);
int condition_lock(condition_t* cond);
int condition_unlock(condition_t* cond);
int condition_wait(condition_t* cond);
int condition_timewait(condition_t* cond, const struct timespec* abstime);
int condition_signal(condition_t* cond);    // v(s)
int condition_broadcast(condition_t* cond);
int condition_destory(condition_t* cond);

#endif  /* end of #ifndef __CONDITION_H_ */
