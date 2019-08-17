#ifndef _AUTOLOCK_H_
#define _AUTOLOCK_H_

#include <pthread.h>
#include <assert.h>
#include "NonCopyable.h"

class CMutex : public NonCopyable
{
public:
    CMutex();
    ~CMutex();
    void lock();
    void unlock();
private:
    pthread_mutex_t m_mutex;
};

class AutoLock : public NonCopyable
{
public:
    AutoLock(CMutex* pmtx);
    ~AutoLock();
private:
    CMutex* m_pMtx;
};

#endif /* _AUTOLOCK_H_ */