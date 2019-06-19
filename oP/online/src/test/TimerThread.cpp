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
    _thread.start();
}

void TimerThread::stop()
{
    _timer.stop();
    _thread.join();
}

}//end of namespace morey
                                                                         

