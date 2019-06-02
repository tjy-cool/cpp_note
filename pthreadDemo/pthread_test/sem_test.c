
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
 
typedef struct __Buf {
    int *buf;       // 缓冲区
    int n;          // 最大缓冲区
    int head;       // 缓冲区头
    int tail;       // 缓冲区尾
    sem_t items;    // 锁定对不存在项目的缓冲区进行操作的消费者
    sem_t slots;    // 锁定对已满缓冲区进行操作的生产者
    sem_t mutex;    // 确保同时只能有一个消费者或生产者对缓存区进行操作
} Buf;
 
// 声明缓冲区
Buf g_buf;
 
// 生产者插入项目
void insert(Buf *b, int item) {
    sem_wait(&b->slots);
    sem_wait(&b->mutex);
    // 插入数据
    b->buf[(++b->tail)%b->n] = item;
    sem_post(&b->mutex);
    // post等价於把信号量加一，令消费者能对缓冲区操作(说明缓冲区状态为非空)
    sem_post(&b->items);
}
 
// 生产者线程
void *manufacturer(void * arg) {
    int i=0;
    for(i=0; i<100; ++i) {
        insert(&g_buf, i);
    }
    return 0;
}
 
// 消费者获取项目
int get(Buf *b) {
    int item;
    sem_wait(&b->items);
    sem_wait(&b->mutex);
    // 获取数据(意义上是删除了缓冲区中一个项目)
    item = b->buf[(++b->head)%b->n];
    sem_post(&b->mutex);
    // post等价于把信号量加一，令生产者能对缓冲区操作(说明缓冲区状态为未满)
    sem_post(&b->slots);
    return item;
}
 
// 消费者线程
void *consumer(void * arg) {
    int i=0, data;
    for(i=0; i<100; ++i) {
        data = get(&g_buf);
        printf("consumer: %d\n", data);
        // 消费者睡300ms， 测试一下看看生产者会不会把缓冲区溢出
        usleep(1000*300);
    }
    return 0;
}
 
int main() {
    pthread_t tid_man, tid_con;
 
    // 设置缓冲区
    g_buf.n = 5;
    g_buf.buf = (int *)malloc(g_buf.n*sizeof(int));
    sem_init(&g_buf.mutex, 0, 1);
    sem_init(&g_buf.slots, 0, g_buf.n);	// g_buf.n也就是允许插入的数量
    sem_init(&g_buf.items, 0, 0);	
    g_buf.head = -1;
    g_buf.tail = -1;
 
    // 创建生产者与消费者线程
    pthread_create(&tid_man, 0, manufacturer, 0);
    pthread_create(&tid_con, 0, consumer, 0);
 
    // 释放已申请的资源
    pthread_join(tid_man, 0);
    pthread_join(tid_con, 0);
    sem_destroy(&g_buf.items);
    sem_destroy(&g_buf.slots);
    sem_destroy(&g_buf.mutex);
 
    return 0;
}
