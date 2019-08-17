#include <iostream>
#include <pthread.h>
#include "AutoLock.h"

using namespace std;


static int cnt = 0;
CMutex mux;

void* proc(void* args)
{
    while(cnt < 100)
    {
        AutoLock lock(&mux);
        cout << "in proc, cnt: " << cnt << endl;
        ++cnt;
    }
    return NULL;
}

int main()
{
    pthread_t th;

    int ret = pthread_create(&th, NULL, proc, NULL);
    if(ret < 0)
    {
        return -1;
    }

    while(cnt < 100)
    {
        AutoLock lock(&mux);
        cout << "in main, cnt: " << cnt << endl;
        ++cnt;
    }
    return 0;
}