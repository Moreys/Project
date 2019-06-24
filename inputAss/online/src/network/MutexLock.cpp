/*************************************************************************
  @FileName:  MutexLock.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 15时59分28秒
 ************************************************************************/

#include "MutexLock.hpp"

namespace morey
{

MutexLock::MutexLock()
: _isLooking(false)
{
    if(pthread_mutex_init(&_mutex, NULL))
    {
        perror("pthread_mutex_init");
    }
}

MutexLock::~MutexLock()
{
    if(pthread_mutex_destroy(&_mutex))
    {
        perror("pthread_mutex_destroy");
    }
}

void MutexLock::lock()
{
    if(pthread_mutex_lock(&_mutex))
    {
        perror("pthread_mutex_lock");
    }
    _isLooking = true;
}
void MutexLock::uinlock()
{
    if(pthread_mutex_unlock(&_mutex))
    {
        perror("pthread_mutex_unlock");
    }
    _isLooking = false;
}

bool MutexLock::isLooking() const
{
    return _isLooking;
}

pthread_mutex_t * MutexLock::getMutexLockPtr()
{
    return & _mutex;
}

MutexLockGuard::MutexLockGuard(MutexLock & mutex)
: _mutex(mutex)
{
    _mutex.lock();
}
MutexLockGuard::~MutexLockGuard()
{
    _mutex.uinlock();
}

}//end of namespace morey


