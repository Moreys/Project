/*************************************************************************
  @FileName:  MutexLock.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 15时59分28秒
 ************************************************************************/
                                                                         
#ifndef __MUTEXLOCK_HPP__
#define __MUTEXLOCK_HPP__
#include "Noncopyable.hpp"

#include <stdio.h>
#include <errno.h>
#include <pthread.h>

namespace morey
{

class MutexLock
: Noncopyable
{
public:
    MutexLock();
    ~MutexLock();
public:
    void lock();
    void uinlock();
    bool isLooking() const;
    pthread_mutex_t * getMutexLockPtr();

private:
    pthread_mutex_t _mutex;
    bool _isLooking;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock & mutex);
    ~MutexLockGuard();
private:
    MutexLock & _mutex;
};

}//end of namespace morey

#endif

