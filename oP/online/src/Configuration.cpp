/*************************************************************************
  @FileName:  Configuration.cpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月15日 星期六 17时40分39秒
 ************************************************************************/

#include "Configuration.hpp"
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
    }
    else
    {
        cout << "ifstream open error" << endl;
        LogError("error message, %s","ifstream open error");
    }
}

string Configuration::getIp() const
{
    string ip;
    auto it = _configMap.find("ip");
    if(it == _configMap.end())
    {
        LogError("error message, %s","读取ip信息出错");
    }
   else
   {
       ip = it->second;
   }
   return ip;
}

unsigned short Configuration::getPort() const
{
    string port;
    auto it = _configMap.find("port");
    if(it == _configMap.end())
    {
        LogError("error message, %s","读取端口号信息出错");
    }
   else
   {
       port = it->second;
   }
   return (short)stoi(port);
}

string Configuration::getEnglishDic() const
{
    string enDic;
    auto it = _configMap.find("enDic");
    if(it == _configMap.end())
    {
        LogError("error message, %s","读取英文词典错误");
    }
   else
   {
       enDic = it->second;
   }
   return enDic;
}
string Configuration::getChianDic() const
{
    string chDic;
    auto it = _configMap.find("chDic");
    if(it == _configMap.end())
    {
        LogError("error message, %s","读取中文词典错误");
    }
   else
   {
       chDic = it->second;
   }
   return chDic;
}

string Configuration::getEnIndex() const
{
    string enIndex;
    auto it = _configMap.find("enIndex");
    if(it == _configMap.end())
    {
        LogError("error message, %s","英文索引路径出错");
    }
   else
   {
       enIndex = it->second;
   }
   return enIndex;
}
string Configuration::getChIndex() const
{
    string chIndex;
    auto it = _configMap.find("chIndex");
    if(it == _configMap.end())
    {
        LogError("error message, %s","读取中文索引路径出错");
    }
   else
   {
       chIndex = it->second;
   }
   return chIndex;

}

void Configuration::debug()
{
    for(auto & elem : _configMap)
    {
        cout << elem.first << "---->" << elem.second << endl;
    }
}

}//end of namespace morey
