/*************************************************************************
  @FileName:  Cache.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月20日 星期四 14时39分29秒
 ************************************************************************/
                                                                         
#ifndef __CACHE_HPP__
#define __CACHE_HPP__
#include <unordered_map>
#include <string>
#include <list>
using std::list;
using std::string;
using std::unordered_map;
namespace morey 
{

class Cache
{
public:
    Cache(int mum);
    Cache(const Cache & cache);
public:
    void addElement(const string & key, const string & value);
    void readFromFile(const string & fileName);
    void writeToFile(const string & fileName);
    void update(const Cache & rhs);
    bool isHaveElement(string & key);
    string  getElement(string & key);

    struct CacheNode
    {
        string key;
        string value;
        CacheNode(string k, string v)
        : key(k)
        , value(v)
        {}
    };

private:
    int _capacity;
    list<CacheNode> _cacheList;
    unordered_map<string, list<CacheNode>::iterator> _hashMap;
    //保存查询次和上传查询的结果返回。下次查询直接命中返回
};

}//end of namespace morey

#endif

