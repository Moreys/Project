/*************************************************************************
  @FileName:  Condition.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 16时19分03秒
 ************************************************************************/
                                                                         
#ifndef __CONDITION_HPP__
#define __CONDITION_HPP__
#include "MutexLock.hpp"

#include <pthread.h>
namespace morey
{

class Condition
: Noncopyable
{
public:
    Condition(MutexLock & mutex);
    ~Condition();

public:
    void notify();
    void notifyAll();
    void wait();

private:
    pthread_cond_t _cond;
    MutexLock & _mutex;
};

}//end of namespace morey

#endif

