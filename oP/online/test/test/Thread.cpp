/*************************************************************************
  @FileName:  Thread.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 17时04分20秒
 ************************************************************************/

#include "Thread.hpp"

#include <errno.h>

using std::cout;
using std::endl;

namespace morey
{

Thread::~Thread()
{
    if(_isRunning)
    {
        pthread_detach(_pthid);
        _isRunning = false;
    }
    cout << "~Thread()" << endl;
}

void Thread::start()
{
    if(pthread_create(&_pthid, nullptr, threadFunc, this))
    {
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}

void Thread::join()
{
    if(_isRunning)
    {
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
}

void * Thread::threadFunc(void * arg)
{
    Thread * pthread = static_cast<Thread*>(arg);
    if(pthread)
        pthread->_cb();

   return nullptr; 
}

}//end of namespace morey


