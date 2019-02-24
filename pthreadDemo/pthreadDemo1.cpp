#include <iostream>
#include <pthread.h>

using namespace std;

static void* func1()
{
    cout << "in func1" << endl;
    for(int i=0; i<10; ++i)
    {
        cout << "i: " << i << endl;
    }
    return NULL;
}

int main()
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, func1, NULL);

    return 0;
}