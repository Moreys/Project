/*************************************************************************
  @FileName:  TaskQueue.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 09:14:24 PM CST
 ************************************************************************/

#include "TaskQueue.h"

#include <iostream>
using namespace std;

namespace morey
{

//function: 队列是否已满
bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

//function: 判断队列是否为空
bool TaskQueue::empty() const
{
    return _que.empty();
}

//function:生产者将产品放入到队列
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

//function: 消费者从队列消费产品
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

void TaskQueue::weakup()
{
    _exitFlag = true;
    _notEmpty.notifyAll();
}

}//end of namespace morey
