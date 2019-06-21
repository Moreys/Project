/*************************************************************************
  @FileName:  Threadpool.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 17时22分28秒
 ************************************************************************/

#include "Threadpool.hpp"
#include "Mylog.hpp"

#include <unistd.h>

namespace morey
{

void Threadpool::start()
{
    std::cout << "线程池启动" << std::endl;
    for(size_t idx = 0; idx != _threadNum; ++idx)
    {
        unique_ptr<Thread> up(new Thread(std::bind(&Threadpool::threadFunc, this)));
        _threads.push_back(std::move(up));
    }
    int number = 0;
    for(auto & thread : _threads)
    {
        thread->start(number);
        number++;
    }
}

void Threadpool::stop()
{
    if(_isExit)
    {
#if 1
        while(!_taskQue.empty())
        {
            ::sleep(1);
            LogInfo("Thread sleep 1 second!");
        }
        _isExit = true;
        LogInfo("线程池退出");
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


