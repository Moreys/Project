/*************************************************************************
  @FileName:  TestMain.cpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月23日 星期日 08时56分03秒
 ************************************************************************/
#include "GlobalDefine.hpp"
#include "Configuration.hpp"

#include <stdio.h>
#include <time.h>

#include <iostream>

using namespace morey;

#define PATH  "/root/project/searchEngline/online/conf/conf.txt"

int main()
{
    Configuration conf(PATH);

#if 1
    conf.debug();
#endif

    std::cout << "Hello world" << std::endl;
    return 0;
}

