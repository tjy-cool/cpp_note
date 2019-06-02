#include <pthread.h>
 #include <unistd.h>
#include <stdio.h>

void* fn1(void* arg)
{
    printf("I am thread fn1, ID: %ld\n", (unsigned long)pthread_self());
    sleep(2);
    return (void*)"hahaha";
}

int main()
{
    pthread_t t1;
    void *rptr;

    pthread_create(&t1, NULL, fn1, NULL);

    sleep(1);

    printf("main thread, ID: %ld\n", (unsigned long)pthread_self());

    pthread_join(t1, &rptr);

    printf("fn1 return %s\n", rptr);
    return 0;
}
