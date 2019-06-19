/*************************************************************************
  @FileName:  Condition.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 08:23:18 PM CST
 ************************************************************************/
                                                                         
#pragma once

#include "Noncopyable.h"
#include "MutexLock.h"

#include <pthread.h>

namespace morey
{

class Condition
: Noncopyable
{
public:
    Condition(MutexLock & mutex)
    : _mutex(mutex)
    {
        if(pthread_cond_init(&_cond, nullptr))
        {
            perror("pthread_cond_init");
        }
    }
    ~Condition() 
    {
        if(pthread_cond_destroy(&_cond))
        {
            perror("pthread_cond_destroy");
        }
    }
public:
    void notify();
    void notifyAll();
    void wait();
    void timedwait(); // 需要另一个参数，没有设置。
private:
    pthread_cond_t _cond;
    MutexLock & _mutex;

};

}//end of namespace morey
