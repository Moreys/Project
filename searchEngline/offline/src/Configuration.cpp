/*************************************************************************
  @FileName:  Configuration.cpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月15日 星期六 17时40分39秒
 ************************************************************************/

#include "Configuration.hpp"
#include "GlobalDefine.hpp"
#include "Mylog.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::ifstream;

namespace morey
{

Configuration::Configuration(const string & filepath)
: _filepath(filepath)
{
    readConfiguration();
    getStopWordList();
}

map<string, string> & Configuration::getConfigMap()
{
    return _configMap;
}

set<string> & Configuration::getStopWordList()
{
    if(_stopWordList.size() > 0)
    {
        return  _stopWordList;
    }
    string stopWordListPath = _configMap[STOPWORD_KEY];
    ifstream ifs(stopWordListPath.c_str());
    if(!ifs)
    {
        LogError("StopWork ifstream open error");
    }
    string word;
    while(getline(ifs, word))
    {
        _stopWordList.insert(word);
    }

#if 1
    for(auto & str : _stopWordList)
    {
        cout << str  << "\t" << str.size() << endl;
    }
#endif

    return _stopWordList;
}

//function: 读取配置文档
void Configuration::readConfiguration()
{
    ifstream ifs(_filepath.c_str());
    if(ifs.good())
    {
        string line;
        while(getline(ifs, line))
        {
            std::istringstream iss(line);
            string key;
            string value;
            iss >> key >> value;
            _configMap[key] = value;
        }
    }
    else
    {
        cout << "ifstream open error" << endl;
        LogError("error message, %s","ifstream open error");
    }
}

void Configuration::debug()
{
    for(auto & elem : _configMap)
    {
        cout << elem.first << "---->" << elem.second << endl;
    }
}

}//end of namespace morey
