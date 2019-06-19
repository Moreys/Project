/*************************************************************************
  @FileName:  Noncopyable.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Mon 10 Jun 2019 08:00:26 PM CST
 ************************************************************************/
                                                                         
#pragma once

namespace morey
{

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable operator=(const Noncopyable &) = delete;
};

}//end of namespace morey;
