/*************************************************************************
  @FileName:  Thread.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 08:55:28 PM CST
 ************************************************************************/
                                                                         
#include "Thread.h"

#include <stdio.h>
#include <errno.h>
#include <iostream>

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

//function: 创建线程
void Thread::start()
{
    if(pthread_create(&_pthid,nullptr, threadFunc, this))
    {
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}

//function: 等待子线程处理完毕 回收子线程
void Thread::join()
{
    if(_isRunning)
    {
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
}

//function: 线程处理函数
//argme: arg:处理函数入口地址
void * Thread::threadFunc(void * arg)
{
    Thread * pthread = static_cast<Thread*>(arg);
    if(pthread)
        pthread->_cb();

    return nullptr;
}

};//end of namespace morey
