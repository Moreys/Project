/*************************************************************************
  @FileName:  Timer.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 18时03分08秒
 ************************************************************************/

#include "Timer.hpp"
#include "Mylog.hpp"

#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>
#include <iostream>

namespace morey
{

void Timer::start()
{
    _isStarted = true;
    setTime(_initSec, _intervalSec);
    struct pollfd pfd;
    pfd.fd = _timerfd;
    pfd.events = POLLIN;
    while(_isStarted)
    {
        int nready = ::poll(&pfd, 1, 5000);
        if(nready == -1 && errno == EINTR)
        {
            continue;
        }
        else if(-1 == nready)
        {
            perror(">> poll error");
            LogError("pool error");
            exit(EXIT_FAILURE);
        }
        else if(0 == nready)
        {
            std::cout << ">> poll timeout" << std::endl;
        }
        else
        {
            if(pfd.revents & POLLIN)
            {
                handleRead();
                if(_cb)
                    _cb();
            }
        }
    }
}

void Timer::stop()
{
    if(_isStarted)
    {
        setTime(0, 0);
        _isStarted = false;
    }
}
Timer::~Timer()
{
    if(_isStarted)
        stop();
}

void Timer::setTime(int initSec, int intervalSec)
{
    struct itimerspec value;
    value.it_value.tv_sec = initSec;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = intervalSec;
    value.it_interval.tv_nsec = 0;
    int ret = ::timerfd_settime(_timerfd, 0, &value, nullptr);
    if(-1 == ret)
    {
        perror(">> timerfd_settime");
    }
}

int Timer::createTimefd()
{
    int fd = ::timerfd_create(CLOCK_REALTIME, 0);
    if(-1 ==fd)
    {
        perror("timerfd_create");
    }
    return fd;
}

void Timer::handleRead()
{
    uint64_t howmany;
    int ret = ::read(_timerfd, &howmany, sizeof(howmany));
    if(ret != sizeof(howmany))
    {
        perror(">> read error");
    }
}


}//end of namespace morey


