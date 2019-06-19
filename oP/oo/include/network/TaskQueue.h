/*************************************************************************
  @FileName:  TaskQueue.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 09:10:18 PM CST
 ************************************************************************/
                                                                         
#pragma once
#include "MutexLock.h"
#include "Condition.h"

#include <queue>
#include <functional>
using std::queue;

namespace morey
{

using Task = std::function<void()>;
using ElemType = Task;
class TaskQueue
{
public:
    TaskQueue(size_t queSize = 10)
    : _queSize(queSize)
    , _notFull(_mutex)
    , _notEmpty(_mutex)
    , _exitFlag(false)
    {}
public:
    bool full() const;
    bool empty() const;
    void push(ElemType &&);
    ElemType pop();
    void weakup();

private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _exitFlag;
};

}//end of namespace morey
