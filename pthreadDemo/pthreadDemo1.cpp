#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

static void* func1(void*)
{
    cout << "in func1" << endl;
    for(int i=0; i<10; ++i)
    {
        sleep(1);
        cout << "in func1 i: " << i << endl;
    }
    return NULL;
}

int main()
{
    pthread_t ptid;
    cout << "in main" << endl;

    
    pthread_create(&ptid, NULL, func1, NULL);
    for(int i=0; i<10; ++i)
    {
        sleep(1);
        cout << "in main i: " << i << endl;
    }
    pthread_join(ptid, NULL);
    return 0;
}