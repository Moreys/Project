/*************************************************************************
  @FileName:  Dictionary.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月19日 星期三 09时39分00秒
 ************************************************************************/

#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__
#include "Configuration.hpp"

#include "pthread.h"

#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace morey
{

struct Result
{
    string _word;
    int _iFreq;
    int _iDist;
};

class Dictionary
{
public:
    Dictionary(const string & dictPath, const string & indexPath)
    {
        ifstream ifsDic(dictPath), ifsIndex(indexPath);
        if(!ifsDic)
        {
            cout << "文件打开错误" << endl;
        }
        if(!ifsIndex)
        {
            cout << "文件打开错误" << endl;
        }
        string line;
        while(getline(ifsDic, line))
        {
            std::istringstream iss(line);
            string key;
            int value;
            iss >> key >> value;
            _dict.push_back(make_pair(key.c_str(),value));
        }
        string line2;
        while(getline(ifsIndex, line2))
        {
            std::istringstream iss(line2);
            string ikey;
            int ivalue;
            iss >> ikey;
            set<int> tmp;
            while(iss >> ivalue)
            {
                tmp.insert(ivalue);
            }
            _indexTable.insert(make_pair(ikey.c_str(),tmp));
        }
    }

public:
    vector<std::pair<string, int>> & getDic()
    {
        return _dict;
    }
    map<string, set< int>> & getIndex()
    {
        return _indexTable;
    }

private:
    vector<std::pair<string, int>> _dict;
    map<string, set<int>> _indexTable;
};

}//end of namespace morey

#endif

