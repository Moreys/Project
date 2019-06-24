/*************************************************************************
  @FileName:  TestMain.cpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月23日 星期日 08时56分03秒
 ************************************************************************/
#include "Configuration.hpp"
#include <iostream>

using namespace morey;

#define PATH  "/root/project/searchEngline/offline/conf/conf.txt"

int main()
{
    Configuration conf(PATH);
    conf.debug();
    set<string> stopWord = conf.getStopWordList();
    std::cout << "Hello world" << std::endl;
    return 0;
}

