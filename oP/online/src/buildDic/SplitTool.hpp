/*************************************************************************
  @FileName:  SplitTool.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月17日 星期一 08时03分10秒
 ************************************************************************/
                                                                         
#ifndef __SPLITTOOL_HPP__
#define __SPLITTOOL_HPP__
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace morey
{
class SplitTool
{
public:
    SplitTool() {}
    virtual ~SplitTool() {}
    virtual vector<string> cut(const string & sentence) = 0;
};

}//end of namespace morey

#endif

