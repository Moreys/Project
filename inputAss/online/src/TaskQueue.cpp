/*************************************************************************
  @FileName:  TaskQueue.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 16时33分03秒
 ************************************************************************/

#include "TaskQueue.hpp"

namespace morey
{

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

bool TaskQueue::empty() const
{
    return _que.empty();
}

void TaskQueue::push(ElemType && number)
{
    {
        MutexLockGuard autolock(_mutex);
        while(full())
        {
            _notFull.wait();
        }
        _que.push(number);
    }
    _notEmpty.notify();
}

ElemType TaskQueue::pop()
{
    ElemType tmp;
    {
        MutexLockGuard autolock(_mutex);
        while(!_exitFlag && empty())
        {
            _notEmpty.wait();
        }
        if(_exitFlag)
        {
            return nullptr;
        }
        tmp = _que.front();
        _que.pop();
    }
    _notFull.notify();
    return tmp;
}

void TaskQueue::weakupEmpty()
{
    _exitFlag = true;
    _notEmpty.notifyAll();
}


}//end of namespace morey


