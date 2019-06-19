/*************************************************************************
  @FileName:  Thread.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 17时04分20秒
 ************************************************************************/
                                                                         
#ifndef __THREAD_HPP__
#define __THREAD_HPP__
#include "Noncopyable.hpp"

#include <pthread.h>
#include <functional>
#include <iostream>

namespace morey
{
class Thread
: Noncopyable
{

using ThreadCallback = std::function<void()>;

public:
    Thread(ThreadCallback && cb)
    : _pthid(0)
    , _isRunning(false)
    , _cb(std::move(cb))
    { std::cout << "Thread()" << std::endl;}

    ~Thread();

public:
    void start();
    void join();
 
private:
    static void * threadFunc(void *);//线程处理函数，通过回调函数进行传入

private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallback _cb;
};

}//end of namespace morey

#endif

