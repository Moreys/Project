/*************************************************************************
  @FileName:  Noncopyable.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 15时57分07秒
 ************************************************************************/
                                                                         
#ifndef __NONCOPYABLE_HPP__
#define __NONCOPYABLE_HPP__

namespace morey
{

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable & operator=(const Noncopyable &) = delete;
};


}//end of namespace morey

#endif

