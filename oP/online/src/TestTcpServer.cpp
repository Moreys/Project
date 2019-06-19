/*************************************************************************
  @FileName:  TestEventLoop.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Thu 13 Jun 2019 05:55:35 PM CST
 ************************************************************************/
                                                                         
#include "SpellcorrectServer.hpp"
#include "Configuration.hpp"
#include "Mylog.hpp"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using namespace morey;


int main()
{
    
    SpellcorrectServer sp(Singleton<Configuration>::getInstance(PATH)->getIp(),
                          Singleton<Configuration>::getInstance(PATH)->getPort(),
                          4, 10);
    sp.start();
    Mylogger::destroy();
    return 0;
}

