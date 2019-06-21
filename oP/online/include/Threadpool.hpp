/*************************************************************************
  @FileName:  Threadpool.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 17时22分28秒
 ************************************************************************/
                                                                         
#ifndef __PTHREADPOOL_HPP__
#define __PTHREADPOOL_HPP__
#include "TaskQueue.hpp"
#include "Thread.hpp"

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

namespace morey
{

class Threadpool
{
public:
    Threadpool(size_t threadNum, size_t queSize)
    : _threadNum(threadNum)
    , _queSize(queSize)
    , _isExit(false)
    {
        _threads.reserve(_threadNum);
    }
public:
    void start();
    void stop();
    void addTask(ElemType &&);
    
private:
    void threadFunc();
    ElemType getTask();

private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskQue;
    bool _isExit;
};


}//end of namespace morey

#endif

