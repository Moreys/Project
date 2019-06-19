/*************************************************************************
  @FileName:  Thread.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 08:43:39 PM CST
 ************************************************************************/
                                                                         
#pragma once
#include "Noncopyable.h"

#include <pthread.h>
#include <functional>
#include <iostream>
namespace morey
{

class Thread
: Noncopyable
{
public:
    using ThreadCallback = std::function<void()>;

    Thread(ThreadCallback && cb)
    : _pthid(0)
    , _isRunning(false)
    , _cb(std::move(cb))
    {   std::cout << "Thread()" << std::endl;}
    ~Thread();
public:
    void start();
    void join();
private:
    static void * threadFunc(void *);
private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallback _cb;
};

}//end of namespace morey
