/*************************************************************************
  @FileName:  Thread.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 17时04分20秒
 ************************************************************************/

#include "Thread.hpp"

#include <errno.h>
#include <iostream>
using namespace morey;


using std::cout;
using std::endl;


namespace morey
{

__thread int tNumber;

using TareadCallback = function<void()>;

struct ThreadData
{
    int _number;
    TareadCallback _cb;
    ThreadData(int number, TareadCallback cb)
    : _number(number)
    , _cb(cb)
    {}

   void runInThread()
   {
       _number = tNumber;
       if(_cb)
           _cb();
   }
};

Thread::~Thread()
{
    if(_isRunning)
    {
        pthread_detach(_pthid);
        _isRunning = false;
    }
    cout << "~Thread()" << endl;
}

void Thread::start(int number)
{
    ThreadData * threadData = new ThreadData(number, _cb);
    if(pthread_create(&_pthid, nullptr, threadFunc,threadData))
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
    ThreadData * pthreadData = static_cast<ThreadData*>(arg);
    if(pthreadData)
        pthreadData->_cb();

   delete pthreadData;
   
   return nullptr; 
}

}//end of namespace morey


