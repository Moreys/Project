/*************************************************************************
  @FileName:  SplitToolNLPIR.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月17日 星期一 08时08分18秒
 ************************************************************************/
                                                                         
#ifndef __SPLITTOOLNLPIR__HPP__
#define __SPLITTOOLNLPIR__HPP__
#include "SplitTool.hpp"
#include "Configuration.hpp"

#include <iostream>
#include <string>
using std::string;

namespace  morey
{

class SplitToolNLPIR
: SplitTool
{
public:
    SplitToolNLPIR(Configuration & config)
    : _config(config)
    {}
    virtual ~SplitToolNLPIR() {}
public:
    virtual vector<string> cut(const string & sentence) = 0;

private:
    Configuration & _config;
};

}//end of namespace morey

#endif

