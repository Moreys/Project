/*************************************************************************
  @FileName:  DictProducer.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月15日 星期六 18时20分11秒
 ************************************************************************/

#include "DictProducer.hpp"
#include "SplitTool.hpp"
#include "Configuration.hpp"
#include "Dictionary.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

namespace morey
{

DictProducer::DictProducer(const string & dir)
    : _dir(dir)
      , _config(_dir)
    {
        get_files();
    }

void DictProducer::init()
{
    build_dict();
    reand_dict();
    build_index();
}

void DictProducer::build_dict()
{
    string ifs, ofs;
    map<string, string>::iterator it = _dict.find("txt");
    if(it == _dict.end())
    {
        cout << "没有找到" << endl;
    }
    else
    {
        ifs = it->second;
    }
    map<string, string>::iterator it2 = _dict.find("dict");
    if(it2 == _dict.end())
    {
        cout << "没有找到" << endl;
    }
    else
    {
        ofs = it2->second;
    }
    _dictionary.dispose(ifs, ofs);
    _dictionary.read(ofs);
    _dictionary.store(ofs);
}

void DictProducer::build_cn_dict()
{

}

void DictProducer::build_index()
{
    int flag = 10;
    string str;
    stringstream stream;
    set<int> setInd;
    for(int idx = 'a'; idx != 'z' + 1; ++idx)
    {
        stream << (char)idx;
        str = stream.str();
        stream.str("");
        for(auto & elem : _vecIdx)
        {
            for(int i = 0; i != flag; ++i)
            {
                if(elem.first[i] == idx)
                {
                    setInd.insert(&elem - &_vecIdx[0]);
                    _mapIdx[str] = setInd;
                    break;
                }
            }
        }
        cout << "完成" << str <<endl;
        setInd.clear();
    }
}

void DictProducer::reand_dict()
{
    string file;
    map<string, string>::iterator it2 = _dict.find("dict");
    if(it2 == _dict.end())
    {
        cout << "没有找到" << endl;
    }
    else
    {
        file = it2->second;
    }
    ifstream ifs(file);
    string line;
    while(getline(ifs, line))
    {
        std::istringstream iss(line);
        string key;
        int value;
        iss >> key >> value;
        _vecIdx.push_back(make_pair(key.c_str(),value));
    }
    ifs.close();
}

#if 0

void DictProducer::show_file() const
{

}

void DictProducer::show_dict() const
{
    for(auto & elem : _dict)
    {
        cout << elem.first << endl
            << elem.second << endl;
    }
}
#endif

void DictProducer::get_files()
{
    _dict = _config.getConfigMap();
}

void DictProducer::push_dict()
{
    string file;
    map<string, string>::iterator it2 = _dict.find("index");
    if(it2 == _dict.end())
    {
        cout << "没有找到" << endl;
    }
    else
    {
        file = it2->second;
    }
    ofstream ofs(file);
    for(auto & elem : _mapIdx)
    {
        ofs << elem.first << " ";
        for(auto & lem : elem.second)
            ofs << lem << " ";
        ofs << endl;
    }
    ofs.close();
}

}//end of namespace morey

