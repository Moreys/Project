/*************************************************************************
  @FileName:  MutexLock.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 07:59:52 PM CST
 ************************************************************************/
                                                                         
#pragma once

#include "Noncopyable.h"

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
namespace morey
{

class MutexLock
: Noncopyable
{
public:
    MutexLock()
    : _isLooking(false)
    {
        if(pthread_mutex_init(&_mutex, NULL))
        {
            perror("pthread_mutex_init");
        }
    }
    ~MutexLock()
    {
        if(pthread_mutex_destroy(&_mutex))
        {
            perror("pthread_mutex_destroy");
        }
    }
public:
    void lock();
    void unlock();
    bool isLocking() const { return _isLooking;  }
    pthread_mutex_t * getMutexLockPtr() { return & _mutex;  }

private:
    pthread_mutex_t _mutex;
    bool _isLooking;
};


class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock & mutex)
    : _mutex(mutex)
    {
        _mutex.lock();
    }
    ~MutexLockGuard()
    {
        _mutex.unlock();
    }
private:
    MutexLock & _mutex;
};

}//endl of namespace morey
