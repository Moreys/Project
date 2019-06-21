/*************************************************************************
  @FileName:  Configuration.cpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月15日 星期六 17时40分39秒
 ************************************************************************/

#include "Configuration.hpp"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


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
string Configuration::getCnTxtPath()
{
    string cndicTxt;
    auto it = _configMap.find("cndictxt");
    if(it == _configMap.end())
    {
        cout << "获取路径错误" << endl;
    }
    else
    {
        cndicTxt = it->second;
    }
    return cndicTxt;
}
string Configuration::getCnDicPath()
{
    string cndict;
    auto it = _configMap.find("cndict");
    if(it == _configMap.end())
    {
        cout << "获取路径错误" << endl;
    }
    else
    {
        cndict = it->second;
    }
    return cndict;
}

string Configuration::getcnFile()
{
    string cnfile;
    auto it = _configMap.find("cnfile");
    if(it == _configMap.end())
    {
        cout << "获取路径错误" << endl;
    }
    else
    {
        cnfile = it->second;
    }
    return cnfile;
}
string Configuration::getCnIdx()
{
    string cnIdx;
    auto it = _configMap.find("cnidx");
    if(it == _configMap.end())
    {
        cout << "获取路径错误" << endl;
    }
    else
    {
        cnIdx = it->second;
    }
    return cnIdx;
}

vector<string> & Configuration::getCndictFile()
{
    struct dirent * pDirInfo;
    DIR * pDir;
    pDir = opendir(getcnFile().c_str());
    if(NULL == pDir)
    {
        perror("open dir fail");
    }
    string name;
    while((pDirInfo = readdir(pDir)) != NULL)
    {
        name = pDirInfo->d_name;
        if(name == "." || name == "..")
        {
            continue;
        }
        _cndictFile.push_back(pDirInfo->d_name);
    }
#if 1
    for(auto & elem : _cndictFile)
    {
        std::cout << elem << std::endl;
    }
#endif
    closedir(pDir);
    return _cndictFile;
}

void Configuration::debug()
{
    for(auto & elem : _configMap)
    {
        cout << elem.first << "---->" << elem.second << endl;
    }
}

}//end of namespace morey
