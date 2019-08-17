#ifndef _THREAD_H_
#define _THREAD_H_

#include "NonCopyable.h"
#include <pthread.h>

class Thread : public NonCopyable
{
public:
    Thread();
    virtual ~Thread();

    int start();
    int join();

    virtual void run() = 0;

    pthread_t getThreadId() const
    { return m_nThreadId; };

private:
    static void * runInThread(void * arg);
    pthread_t m_nThreadId;
    bool m_bIsRunning;
};

#endif  /* _THREAD_H_ */