/*************************************************************************
  @FileName:  Noncopyable.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月23日 星期日 08时23分46秒
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

}

#endif


