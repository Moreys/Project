/*************************************************************************
  @FileName:  TimerThread.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 20时52分03秒
 ************************************************************************/
#include "TimerThread.hpp"

namespace morey
{

    
void TimerThread::start()
{
    _thread.start(0);
    _isStart = true;
}

void TimerThread::stop()
{
    if(_isStart)
    {
        _timer.stop();
        _thread.join();
        _isStart = false;
    }
}

}//end of namespace morey
                                                                         

