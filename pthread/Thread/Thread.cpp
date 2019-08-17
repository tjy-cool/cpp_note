#include "Thread.h"

Thread::Thread() 
 : m_nThreadId(0)
 , m_bIsRunning(false)
{
}

Thread::~Thread()
{

}

void * Thread::runInThread(void *arg)
{
    Thread *pt = static_cast<Thread*>(arg);
    pt->run();
    return NULL;
}

int Thread::start()
{
    int nRet = pthread_create(&m_nThreadId, NULL, Thread::runInThread, this);
    if ( nRet < 0)
    {
        return nRet;
    }
    m_bIsRunning = true; 
    return 0;
}

int Thread::join()
{
    if (!m_bIsRunning)
    {
        return -1;  // 这里需要自定义错误码
    }
    
    int nRet = pthread_join(m_nThreadId, NULL);
    if (0 == nRet)
    {
        m_bIsRunning = false;
    }
    
    return nRet;
}