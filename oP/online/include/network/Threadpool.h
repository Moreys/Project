/*************************************************************************
  @FileName:  Threadpool.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 04:32:43 PM CST
 ************************************************************************/
                                                                         
#pragma once

#include "TaskQueue.h"
#include "Thread.h"

#include <vector>
#include <memory>

using namespace std;

namespace morey
{

class Threadpool
{
    friend class WorkerThread;
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
    void threadFun();
    ElemType getTask();
private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskque;
    bool _isExit;
};

}//end of namespace morey

