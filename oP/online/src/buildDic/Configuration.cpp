/*************************************************************************
  @FileName:  Configuration.cpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月15日 星期六 17时40分39秒
 ************************************************************************/

#include "Configuration.hpp"

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
}

map<string, string> & Configuration::getConfigMap()
{
    return _configMap;
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
        cout << "readConfiguration is over" << endl;
    }
    else
    {
        cout << "ifstream open error" << endl;
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
