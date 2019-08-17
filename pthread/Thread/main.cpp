#include "Thread.h"
#include <unistd.h>
#include <iostream>

using namespace std;

class MyThread : public Thread
{
public:
    void run()
    {
        cout << "foo" << endl;
    }
};

int main()
{
    MyThread t;
    t.start();
    t.join();

    return 0;
}