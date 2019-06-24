/*************************************************************************
  @FileName:  SplitToolCppJieba.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月17日 星期一 08时53分34秒
 ************************************************************************/
                                                                         
#ifndef __SPLITTOOLCPPJIEBA_HPP__
#define __SPLITTOOLCPPJIEBA_HPP__

#include "Configuration.hpp"
#include "SplitTool.hpp"

namespace morey
{

class SplitToolCppJieba
{
public:
    SplitToolCppJieba(Configuration & config)
    : _config(config)
    {}
    virtual~SplitToolCppJieba() {}
public:
    virtual vector<string> cut(const string & sentence) = 0;

private:
    Configuration & _config;
};


}//end of namespace morey

#endif

