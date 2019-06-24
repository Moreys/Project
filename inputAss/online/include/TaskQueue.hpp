/*************************************************************************
  @FileName:  TaskQueue.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 16时33分03秒
 ************************************************************************/

#ifndef __TASKQUEUE_HPP__
#define __TASKQUEUE_HPP__
#include "MutexLock.hpp"
#include "Condition.hpp"

#include <queue>
#include <functional>
using std::queue;

namespace morey
{

using ElemType = std::function<void()>;

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
    void weakupEmpty();
private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _exitFlag;
};

}//end of namespace morey

#endif

