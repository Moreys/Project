/*************************************************************************
  @FileName:  Condition.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 10:03:13 PM CST
 ************************************************************************/
                                                                         
#include "MutexLock.hpp"

namespace morey
{

//function:互斥锁加锁
void MutexLock::lock()
{
    if(pthread_mutex_lock(&_mutex))
    {
        perror("pthread_mutex_lock");
    }
    _isLooking = true;
}

//function:互斥锁解锁
void MutexLock::unlock()
{
    if(pthread_mutex_unlock(&_mutex))
    {
        perror("pthread_mutex_unlock");
    }
    _isLooking = false;
}

}//end of namespace morey
