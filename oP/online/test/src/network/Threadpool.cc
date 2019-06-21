/*************************************************************************
  @FileName:  Threadpool.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 04:40:31 PM CST
 ************************************************************************/

#include "Threadpool.h"

#include <unistd.h>

namespace morey
{
//function:开启线程池
void Threadpool::start()
{
    for(size_t idx = 0; idx != _threadNum; ++idx)
    {
        unique_ptr<Thread> up(new Thread(std::bind(&Threadpool::threadFun, this)));
        _threads.push_back(std::move(up));
    }
    for(auto & thread : _threads)
    {
        thread->start();
    }
}

//function:结束线程池
void Threadpool::stop()
{
    if(!_isExit)
    {
        //当任务队列中还有没有执行完毕，等待
        while(!_taskque.empty())
        {
            ::sleep(1);
           // ::usleep(1000);
        }

        //存在潜在风险：当_isExit被修改时，任务已经执行完毕了
        //每一个子线程都阻塞在了getTask方法之上，此时再将_isExit设置为true已经没有意义了
        _isExit = true;
        _taskque.weakup();
        for(auto & thread : _threads)
        {
            thread->join();
        }
    }
}

//function:添加任务到线程池队列
//pragma: task:任务的函数指针
void Threadpool::addTask(ElemType && task)
{
    _taskque.push(std::move(task));
}

//function:线程处理函数 子线程中执行。主线程执行的任务
//只负责分发任务给子线程
void Threadpool::threadFun()
{
    while(!_isExit)
    {
        ElemType  task = getTask();
        if(task)
        {
            task();//执行任务是有时间的
        }
    }
}

//function:获取队列里面的任务
//return: 返回任务地址
ElemType Threadpool::getTask()
{
    return _taskque.pop();
}

}//end of namespace std;

