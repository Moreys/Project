/*************************************************************************
  @FileName:  Dictionary.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月19日 星期三 09时39分00秒
 ************************************************************************/

#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__
#include "Configuration.hpp"
#include "Mylog.hpp"

#include "pthread.h"

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
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
    Dictionary(const string & enDicPath, const string & enIdxPath,
               const string & cnDicPath, const string & cnIdxPath);

    void init(const string & enDicPath, const string & enIdxPath,
               const string & cnDicPath, const string & cnIdxPath);
    

public:
    vector<std::pair<string, int>> & getenDic();
    vector<std::pair<string, int>> & getcnDic();
    unordered_map<string, set< int>> & getenIdx();
    unordered_map<string, set< int>> & getcnIdx();

private:
    vector<std::pair<string, int>> _enDict;
    vector<std::pair<string, int>> _cnDict;
    unordered_map<string, set<int>> _enIdx;
    unordered_map<string, set<int>> _cnIdx;

};

}//end of namespace morey

#endif

