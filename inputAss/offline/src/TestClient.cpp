/*************************************************************************
  @FileName:  test.cpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月15日 星期六 18时05分03秒
 ************************************************************************/
                                                                         
#include "DictProducer.hpp"

#include <iostream>
using std::cout;
using std::endl;
#define PATH "/root/project/inputAss/offline/conf/dicq.conf"
int main()
{
    morey::DictProducer myconfig(PATH);
    return 0;
}


