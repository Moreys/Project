/*************************************************************************
  @FileName:  Condition.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 08:23:18 PM CST
 ************************************************************************/
#include "Condition.hpp"                                                                         

namespace morey
{

//function: 激活一个等待条件
void Condition::notify()
{
    if(pthread_cond_signal(&_cond))
    {
        perror("pthread_cond_signal");
    }
}

//function: 激活所有等待条件
void Condition::notifyAll()
{
    if(pthread_cond_broadcast(&_cond))
    {
        perror("pthread_cond_broadcast");
    }
}

//function: 无条件等待
void Condition::wait()
{
    if(pthread_cond_wait(&_cond, _mutex.getMutexLockPtr()))
    {
        perror("pthread_cond_wait");    
    }
}

}//end of namespace morey
