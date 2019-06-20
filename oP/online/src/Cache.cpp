/*************************************************************************
  @FileName:  Cache.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月20日 星期四 14时39分29秒
 ************************************************************************/

#include "Cache.hpp"
#include "Mylog.hpp"
#include <fstream>
using namespace std;

namespace morey 
{

Cache::Cache(int mum)
: _capacity(mum)
{}

bool Cache::isHaveElement(string & key)
{
   auto it = _hashMap.find(key);
   if(it == _hashMap.end())
   {
       return false;
   }
   return true;
}

string Cache::getElement(string & key)
{
    auto it = _hashMap.find(key);
    if(it == _hashMap.end())
    {
        cout << "没有缓存数据" << endl;
        return NULL;
    }
    else
    {
        string value = it->second->value;
        _cacheList.splice(_cacheList.begin(), _cacheList, it->second);
        _hashMap[key] = _cacheList.begin();
        return value;
    }
}

void Cache::addElement(const string & key, const string & value)
{
    auto it = _hashMap.find(key);
    if(it == _hashMap.end())
    {
        if((int)_cacheList.size() == _capacity)
        {
            string key = _cacheList.back().key;
            _hashMap.erase(key);
            _cacheList.pop_back();
        }
        _cacheList.push_front(CacheNode(key,value));
        _hashMap.insert(make_pair(key, _cacheList.begin()));
    }
    else
    {
        it->second->value = value;
        _cacheList.splice(_cacheList.begin(), _cacheList, it->second);
        _hashMap[key] = _cacheList.begin();
    }
}

void Cache::readFromFile(const string & fileName)
{
    ifstream ifs(fileName);
    if(!ifs)
    {
        LogError("读取文件路径错误");
    }
    string line;
    while(getline(ifs, line))
    {
        istringstream iss(line);
        string key, value;
        iss >> key >> value;
        CacheNode node(key, value);
        _cacheList.push_back(node);
    }
}

void Cache::writeToFile(const string & fileName)
{
    ofstream ofs(fileName);
    if(ofs.good())
    {
        for(auto & elem : _cacheList)
        {
            ofs << elem.key << "  ";
            ofs << elem.value << endl;
        }
    }
    else
    {
        LogError("打开文件错误");
    }
    ofs.close();
}

void Cache::update(const Cache & rhs)
{
    for(auto & elem : rhs._hashMap)    
    {
        auto cit = _hashMap.find(elem.first);
        if(cit == _hashMap.end())
        {
            _hashMap.insert(std::move(elem));
        }
    }
}

}//end of namespace morey


