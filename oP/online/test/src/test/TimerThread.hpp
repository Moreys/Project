/*************************************************************************
  @FileName:  TimerThread.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 20时52分03秒
 ************************************************************************/

#ifndef __TIMERTHREAD_HPP__
#define __TIMERTHREAD_HPP__
#include "Thread.hpp"
#include "Timer.hpp"
namespace morey
{

class TimerThread
{
    using TimerCallback = std::function<void()>;
public:
    TimerThread(int initSec, int intervalSec, TimerCallback && cb)
    : _timer(initSec, intervalSec, std::move(cb))
    , _thread(std::bind(&Timer::start, &_timer))
    {}
public:
    void start();
    void stop();
private:
    Timer _timer;
    Thread _thread;
};

}//end of namespace morey

#endif
                                                                         

