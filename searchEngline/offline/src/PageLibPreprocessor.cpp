/*************************************************************************
  @FileName:  PageLibPreprocessor.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 22时13分27秒
 ************************************************************************/

#include "PageLibPreprocessor.hpp"
#include "PageLib.hpp"

#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::stringstream;

namespace morey
{

PageLibPreprocessor::
    PageLibPreprocessor(Configuration & conf)
    : _conf(conf)
{}

void PageLibPreprocessor::
doProcess()
{

}

void PageLibPreprocessor::
readInfoFromFile()
{

}

void PageLibPreprocessor::
cutRedundantPages()
{

}

void PageLibPreprocessor::
buildInvertIdxTable()
{

}

void PageLibPreprocessor::
storeOnDisk()
{

}



}//end of namespace morey


