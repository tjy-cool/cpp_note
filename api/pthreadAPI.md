# pthread API

## 线程  pthread_t

```c
/* 头文件 */
#include <pthread.h>

/* 创建线程 */
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine)(void *), void *arg);

/* 等待一个线程的结束, 线程间同步的操作 */
int pthread_join(pthread_t thread, void **value_ptr);

/* 以分离的方式让子线程运行，子线程与父线程无关，直到子线程遇到return或pthread_exit才退出 */
int pthread_deatch(pthread_t thread);

/* 取消线程 */
int pthread_cancel(pthread_t thread);

/* 线程退出，退出码为value_ptr，在主线程中调用pthread_join可以获取该退出码 */
void pthread_exit(void *value_ptr);
```

## 线程互斥 —— 互斥锁 pthread_mutex_t

```c
/* 初始化mutex, 此方法为静态初始化方法，静态方法和动态方法只能使用一种 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* 初始化mutex, 此方法为动态初始化方法，必须与pthread_mutex_destroy配套使用 */
int pthread_mutex_init(pthread_mutex_t *restrict, const pthread_mutexattr_t *restrict);

/* 销毁mutex, 必须与pthread_mutex_init配套使用, 且如果mutex是指针，调用该方法后需要调用free */
int pthread_mutex_destroy(pthread_mutex_t *mutex);

/* 非阻塞的锁定互斥锁，如果指定的互斥锁已经被锁定的话，立即返回一个值来描述互斥锁的状况错误码，加锁成功返回0 */
int pthread_mutex_trylock(pthread_mutex_t *mutex);

/* 阻塞的锁定互斥锁，如果指定的互斥锁已经被锁定，则阻塞，否则对指定互斥锁上锁 */
int pthread_mutex_lock(pthread_mutex_t *mutex);

/* 对指定的互斥锁解锁 */
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

- 使用实例

```c
pthread_mutex_t lock;
pthread_mutex_init(&lock,NULL);
pthread_mutex_lock(&lock);
// 这里是临界区
pthread_mutex_unlock(&lock);
pthread_mutex_destory(&lock);
```

## 线程同步 —— 条件变量  pthread_cond_t

```c
/* 初始化一个条件变量 */
int pthread_cond_init (pthread_cond_t* cond, pthread_condattr_t *cond_attr);
 
/* 销毁一个条件变量 */
int pthread_cond_destroy(pthread_cond_t* cond);
 
/* 令一个消费者等待在条件变量上 */
int pthread_cond_wait(pthread_cond_t* cond);
 
/* 生产者通知等待在条件变量上的消费者 */
int pthread_cond_signal(pthread_cond_t* cond);
 
/* 生产者向消费者广播消息 */
int pthread_cond_broadcast(pthread_cond_t* cond);
```

- 消费者伪代码

```c
pthread_mutex_lock(&mutex); // 拿到互斥锁，进入临界区
while( 条件为假)
        pthread_cond_wait(cond, mutex); // 令进程等待在条件变量上
修改条件
pthread_mutex_unlock(&mutex); // 释放互斥锁
```

- 生产者伪代码

```c
pthread_mutex_lock(&mutex); // 拿到互斥锁，进入临界区
设置条件为真
pthread_cond_signal(cond); // 通知等待在条件变量上的消费者
pthread_mutex_unlock(&mutex); // 释放互斥锁
```
