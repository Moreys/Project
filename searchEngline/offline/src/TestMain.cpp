/*************************************************************************
  @FileName:  TestMain.cpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月23日 星期日 08时56分03秒
 ************************************************************************/
#include "GlobalDefine.hpp"
#include "Configuration.hpp"
#include "DirScanner.hpp"
#include "PageLib.hpp"
#include "Segmentation.hpp"
#include "WebPage.hpp"
#include "PageLibPreprocessor.hpp"

#include <stdio.h>
#include <time.h>

#include <iostream>

using namespace morey;

#define PATH  "/root/project/searchEngline/offline/conf/conf.txt"

int main()
{
    Configuration conf(PATH);

    morey::DirScanner files(conf);
    files();
#if 1
    conf.debug();
    files.debug();
#endif

#if 1
    PageLib paglib(conf, files);
    time_t t1 = time(NULL);
    paglib.create();
    paglib.store();
    time_t t2 = time(NULL);
    cout << "创建网页库时间为：" << (t2 - t1) << endl;
#endif

#if 1
    PageLibPreprocessor libProcessor(conf);
    libProcessor.doProcess();
#endif
    std::cout << "Hello world" << std::endl;
    return 0;
}

