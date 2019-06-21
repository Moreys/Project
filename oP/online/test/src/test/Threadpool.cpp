/*************************************************************************
  @FileName:  Threadpool.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 17时22分28秒
 ************************************************************************/

#include "Threadpool.hpp"

#include <unistd.h>

namespace morey
{

void Threadpool::start()
{
    for(size_t idx = 0; idx != _threadNum; ++idx)
    {
        unique_ptr<Thread> up(new Thread(std::bind(&Threadpool::threadFunc, this)));
        _threads.push_back(std::move(up));
    }
    for(auto & thread : _threads)
    {
        thread->start();
    }
}

void Threadpool::stop()
{
    if(_isExit)
    {
#if 0
        while(!_taskQue.empty())
        {
            
        }
#endif

#if 1
        _isExit = true;
        _taskQue.weakupEmpty();
        for(auto & thread : _threads)
        {
            thread->join();
        }
#endif
    }
}

void Threadpool::addTask(ElemType && task)
{
    _taskQue.push(std::move(task));
}

void Threadpool::threadFunc()
{
    while(!_isExit)
    {
        ElemType task = getTask();
        if(task)
        {
            task();
        }
    }
}

ElemType Threadpool::getTask()
{
    return _taskQue.pop();
}

}//end of namespace morey


