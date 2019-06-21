/*************************************************************************
  @FileName:  Condition.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 16时19分03秒
 ************************************************************************/
#include "Condition.hpp"                                                                         

namespace morey
{

Condition::Condition(MutexLock & mutex)
: _mutex(mutex)
{
    if(pthread_cond_init(&_cond, nullptr))
    {
        perror("pthread_cond_init");
    }
}
Condition::~Condition()
{
    if(pthread_cond_destroy(&_cond))
    {
        perror("pthread_cond_destroy");
    }
}

void Condition::notify()
{
    if(pthread_cond_signal(&_cond))
    {
        perror("pthread_cond_signal");
    }
}
void Condition::notifyAll()
{
    if(pthread_cond_broadcast(&_cond))
    {
        perror("pthread_cond_broadcast");
    }
}
void Condition::wait()
{
    if(pthread_cond_wait(&_cond, _mutex.getMutexLockPtr()))
    {
        perror("pthread_cond_wait");
    }
}

}//end of namespace morey


