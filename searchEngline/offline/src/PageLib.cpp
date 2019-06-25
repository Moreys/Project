/*************************************************************************
  @FileName:  PageLib.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 17时12分57秒
 ************************************************************************/

#include "Configuration.hpp"
#include "PageLib.hpp"
#include "DirScanner.hpp"
#include "RssReader.hpp"
#include "GlobalDefine.hpp"
#include "Mylog.hpp"

#include <iostream>
#include <fstream>

namespace morey
{
PageLib::PageLib(Configuration & conf, DirScanner & dirScanner)
: _conf(conf)
, _dirScanner(dirScanner)
{}


void PageLib::create()
{
    vector<string> & vecFiles = _dirScanner.files();
    RssReader reader(vecFiles);
    reader.loadFeedFiles();
    reader.makePages(_vecFiles);
}

void PageLib::store()
{
    map<string, string> & confMap = _conf.getConfigMap();
    string pageLibPath = confMap[RIPEPAGELIB_KEY];
    string offsetLibPath = confMap[OFFSETLIB_KEY];

    std::ofstream ofsPage(pageLibPath.c_str());
    std::ofstream ofsOffset(offsetLibPath.c_str());
    if(!(ofsPage.good() && ofsOffset.good()))
    {
        LogError("ofstream open orror!");
    }
    for(size_t idx = 0; idx != _vecFiles.size(); ++idx)
    {
        int id = idx + 1;
        int length = _vecFiles[idx].size();
        std::ofstream::pos_type offset = ofsPage.tellp();
        ofsPage << _vecFiles[idx];
        ofsOffset << id << '\t' << offset << '\t' << length << '\n';
    }
    ofsPage.close();
    ofsOffset.close();
}

}//end if namespace morey


