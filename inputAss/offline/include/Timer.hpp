/*************************************************************************
  @FileName:  Timer.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 18时03分08秒
 ************************************************************************/
                                                                         
#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <functional>

namespace morey
{

class Timer
{
    using TimerCallback = std::function<void()>;
public:
    Timer(int initSec, int intervalSec, TimerCallback && cb)
    : _timerfd(createTimefd())
    , _initSec(initSec)
    , _intervalSec(intervalSec)
    , _isStarted(false)
    , _cb(std::move(cb))
    {}
    ~Timer();
public:
    void start();
    void stop();
    void setTime(int, int);
private:
    int createTimefd();
    void handleRead();

private:
    int _timerfd;
    int _initSec;
    int _intervalSec;
    bool _isStarted;
    TimerCallback _cb;
};

}

#endif

