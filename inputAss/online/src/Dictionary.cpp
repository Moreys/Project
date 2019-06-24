/*************************************************************************
  @FileName:  Dictionary.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月19日 星期三 09时39分00秒
 ************************************************************************/

#include "Dictionary.hpp"

using namespace std;

namespace morey
{

Dictionary::Dictionary(const string & enDicPath, const string & enIdxPath,
               const string & cnDicPath, const string & cnIdxPath)
{
    init(enDicPath, enIdxPath, cnDicPath, cnIdxPath);
}

#if 1
void Dictionary::init(const string & enDicPath, const string & enIdxPath,
               const string & cnDicPath, const string & cnIdxPath)
    {
        ifstream ifsenDic(enDicPath), ifsenIdx(enIdxPath);
        ifstream ifscnDic(cnDicPath), ifscnIdx(cnIdxPath);
        cout << cnIdxPath;
        

        if(!ifsenDic || !ifscnDic || !ifsenIdx || !ifscnIdx)
        {
            cout << "文件打开错误" << endl;
            LogError("文件打开错误");
        }
        string line;
        string line2;
        string line3;
        string line4;
        while(getline(ifsenDic, line))
        {
            std::istringstream iss(line);
            string key;
            int value;
            iss >> key >> value;
            _enDict.push_back(make_pair(key.c_str(),value));
        }
        while(getline(ifscnDic, line2))
        {
            istringstream iss(line2);
            string key;
            int value;
            iss >> key >> value;
            _cnDict.push_back(make_pair(key.c_str(),value));
        }
        while(getline(ifsenIdx, line3))
        {
            std::istringstream iss(line3);
            string ikey;
            int ivalue;
            iss >> ikey;
            set<int> tmp;
            while(iss >> ivalue)
            {
                tmp.insert(ivalue);
            }
            _enIdx.insert(make_pair(ikey.c_str(),tmp));
        }
        while(getline(ifscnIdx, line4))
        {
            std::istringstream iss(line4);
            string ikey;
            int ivalue;
            iss >> ikey;
            set<int> tmp;
            while(iss >> ivalue)
            {
                tmp.insert(ivalue);
            }
            _cnIdx.insert(make_pair(ikey.c_str(),tmp));
        }

#if 0 //测试单个文件是否可以获取
    for(auto & elem : _enIdx)
    {
        cout << elem.first << endl;
    }
#endif
#if 0
        _dict.insert(_dict.end(), _enDict.begin(), _enDict.end());
        _dict.insert(_dict.end(), _cnDict.begin(), _cnDict.end());
        _idx.insert(_enIdx.begin(), _enIdx.end());
        _idx.insert(_cnIdx.begin(), _cnIdx.end());
#endif
        ifscnDic.close();
        ifsenDic.close();
        ifsenIdx.close();
        ifscnIdx.close();
    }
#endif
    
    vector<std::pair<string, int>> & Dictionary::getenDic()
    {
        return _enDict;
    }

    unordered_map<string, set< int>> & Dictionary::getenIdx()
    {
        return _enIdx;
    }
    vector<std::pair<string, int>> & Dictionary::getcnDic()
    {
        return _cnDict;
    }

    unordered_map<string, set< int>> & Dictionary::getcnIdx()
    {
        return _cnIdx;
    }
}//end of namespace morey


