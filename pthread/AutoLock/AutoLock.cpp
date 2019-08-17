
#include "AutoLock.h"

CMutex::CMutex() 
{
    pthread_mutex_init(&m_mutex, NULL);
}

CMutex::~CMutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void CMutex::lock()
{
    pthread_mutex_lock(&m_mutex);
}

void CMutex::unlock()
{
    pthread_mutex_unlock(&m_mutex);
}

AutoLock::AutoLock(CMutex* pmtx) : m_pMtx(pmtx)
{
    m_pMtx->lock();
}

AutoLock::~AutoLock()
{
    m_pMtx->unlock();
}
