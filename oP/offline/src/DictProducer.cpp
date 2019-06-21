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
#include "Segmentation.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

namespace morey
{

typedef string  Character;

DictProducer::DictProducer(const string & dir)
    : _dir(dir)
      , _config(_dir)
    {
        get_files();
    }

void DictProducer::init()
{
#if 0 //英文词典索引的建立
    build_dict();
    reand_dict();
    build_index();
#endif

#if 1 //中文词典索引的建立
    //build_cn_dict();
    //push_cndict();
    reand_cndict();
    build_cnIndex();
    push_cnIndex();
#endif
}

vector<string> DictProducer::getOneChareacter( const string & word)
{
    auto cit = word.begin();
    vector<Character> ret;

#if 1
    while(cit < word.end())
    {
        if(224 == (*cit & 224))
        {
            Character temp;
            temp.append(cit, cit + 3);
            ret.push_back(temp);
            cit = cit + 3;
        }
        else if(240 == (*cit & 240))
        {
            Character tmp;
            tmp.append(cit, cit + 4);
            ret.push_back(tmp);
            cit = cit + 4;
        }
        else
        {
            Character tmp(1, *cit);
            ret.push_back(tmp);
            cit++;
        }
    }
#endif
    return ret;
}

void DictProducer::build_dict()
{
    string ifs, ofs;
    map<string, string>::iterator it = _endict.find("txt");
    if(it == _endict.end())
    {
        cout << "没有找到" << endl;
    }
    else
    {
        ifs = it->second;
    }
    map<string, string>::iterator it2 = _endict.find("dict");
    if(it2 == _endict.end())
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
    Segmentation wordSeg;
    vector<string> cnfileVec = _config.getCndictFile();
    vector<string> temp;
    string cnfile;
    for(auto & elem : cnfileVec)
    {
        cnfile = _config.getcnFile() + elem.c_str();
        cout << cnfile << endl;
        ifstream ifsCnT(cnfile);
        if(!ifsCnT)
        {
            cout << "获取中文文件获取错误" << endl;
        }
        string line;
        while(getline(ifsCnT, line))
        {
            vector<string> results = wordSeg(line);
            for(auto it = results.begin(); it != results.end(); ++it)
            {
                temp.push_back(*it);
            }
        }
        ifsCnT.close();
    }

    for(auto & elem : temp)
    {
        map<string, int>::iterator it = _cndict.find(elem);
        if(it == _cndict.end())
        {
            _cndict.insert(map<string,int>::value_type(elem,1));
        }
        else
        {
            ++_cndict[elem];
        }
    }

}

void DictProducer::build_enIndex()
{
    int flag = 15;
    string str;
    stringstream stream;
    set<int> setInd;
    for(int idx = 'a'; idx != 'z' + 1; ++idx)
    {
        stream << (char)idx;
        str = stream.str();
        stream.str("");
        for(auto & elem : _enIdx)
        {
            for(int i = 0; i != flag; ++i)
            {
                if(elem.first[i] == idx)
                {
                    setInd.insert(&elem - &_enIdx[0]);
                    _enMapIdx[str] = setInd;
                    break;
                }
            }
        }
        cout << "完成" << str <<endl;
        setInd.clear();
    }
}

void DictProducer::build_cnIndex()
{
    string key;
    stringstream stream;
    set<int> setInd;
    vector<string> vectmp;
    vector<string> vectmp2;
    for(auto & elem : _cnIdx)
    {
        vectmp = getOneChareacter(elem.first);
        key = vectmp[0];
        for(auto & elem2 : _cnIdx) 
        {
            vectmp2 = getOneChareacter(elem2.first);
            for(auto & elem3 : vectmp2)
            {
                if(key == elem3)
                {
                    setInd.insert(&elem2- &_cnIdx[0]);
                    _cnMapIdx[key] = setInd;
                    break;
                }
            }
        }
        setInd.clear();
    }
#if 0
    for(int idx = 'a'; idx != 'z' + 1; ++idx)
    {
        stream << (char)idx;
        str = stream.str();
        stream.str("");
        for(auto & elem : _enIdx)
        {
            for(int i = 0; i != flag; ++i)
            {
                if(elem.first[i] == idx)
                {
                    setInd.insert(&elem - &_enIdx[0]);
                    _enMapIdx[str] = setInd;
                    break;
                }
            }
        }
    }
#endif
}

void DictProducer::reand_endict()
{
    string file;
    map<string, string>::iterator it2 = _endict.find("dict");
    if(it2 == _endict.end())
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
        _enIdx.push_back(make_pair(key.c_str(),value));
    }
    ifs.close();
}

void DictProducer::reand_cndict()
{
    ifstream ifs(_config.getCnDicPath());
    if(!ifs)
    {
        cout << "获取中文字典路径错误" << endl;
    }
    string line;
    while(getline(ifs, line))
    {
        std::istringstream iss(line);
        string key;
        int value;
        iss >> key >> value;
        _cnIdx.push_back(make_pair(key.c_str(),value));
    }
    ifs.close();

#if 0 //将中文词典读入内容没有问题
    for(auto & elem : _cnIdx)
    {
        cout << elem.first << elem.second << endl;
    }
#endif

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
    _endict = _config.getConfigMap();
}

void DictProducer::push_cndict()
{
    ofstream ofsCnT(_config.getCnDicPath());
    if(!ofsCnT)
    {
        cout << "获取文件错误" << endl;
        return;
    }
    for(const auto & elem : _cndict)
    {
        ofsCnT << elem.first << "    " << elem.second << endl;
    }
    ofsCnT.close();
}

void DictProducer::push_endict()
{
    string file;
    map<string, string>::iterator it2 = _endict.find("index");
    if(it2 == _endict.end())
    {
        cout << "没有找到" << endl;
    }
    else
    {
        file = it2->second;
    }
    ofstream ofs(file);
    for(auto & elem : _enMapIdx)
    {
        ofs << elem.first << " ";
        for(auto & lem : elem.second)
            ofs << lem << " ";
        ofs << endl;
    }
    ofs.close();
}

void DictProducer::push_cnIndex()
{
    ofstream ofs(_config.getCnIdx());
    for(auto & elem : _cnMapIdx)
    {
        ofs << elem.first << " ";
        for(auto & lem : elem.second)
            ofs << lem << " ";
        ofs << endl;
    }
    ofs.close();
}

}//end of namespace morey

