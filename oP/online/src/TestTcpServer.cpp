/*************************************************************************
  @FileName:  Dictionary.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月19日 星期三 09时39分00秒
 ************************************************************************/
#include "SpellcorrectServer.hpp"
#include "Configuration.hpp"
#include "TimerThread.hpp"
#include "CacheManager.hpp"
#include "Mylog.hpp"
#include "Dictionary.hpp"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using namespace morey;
using namespace std;


int main()
{
#if 0
        vector<pair<string, int>> dict = (Singleton<Dictionary>::getInstance(
                  Singleton<Configuration>::getInstance(PATH)->getEnDic(),                                             
                  Singleton<Configuration>::getInstance(PATH)->getEnIdx(),
                  Singleton<Configuration>::getInstance(PATH)->getCnDic(),
                  Singleton<Configuration>::getInstance(PATH)->getCnIdx()
                  ))->getDic();
#if 1
        for(auto & elem : dict)
        {
            cout << elem.first << "  " << elem.second << endl;
#if 0
            for(auto & elem1 : elem.second)
            {
                cout << elem1 << endl;
            }
#endif
            ::usleep(50000);
        }
#endif
#endif





#if 1
        CacheManager * cacheManage = Singleton<CacheManager>::
        getInstance(Singleton<Configuration>::
                    getInstance(PATH)->getCachePath());
    TimerThread timer(1,40,std::bind(&CacheManager::periodicUpdateCache, cacheManage));
    timer.start();
    SpellcorrectServer sp(Singleton<Configuration>::getInstance(PATH)->getIp(),
                          Singleton<Configuration>::getInstance(PATH)->getPort(),
                          4, 10);
    sp.start();
    Mylogger::destroy();
#endif

    return 0;
}
