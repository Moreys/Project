/*************************************************************************
  @FileName:  Cache.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月20日 星期四 14时39分29秒
 ************************************************************************/

#include "Cache.hpp"
#include "Thread.hpp"
#include "Mylog.hpp"
#include <fstream>
#include <sstream>
using namespace std;

namespace morey 
{

Cache::Cache(int mum)
: _capacity(mum)
{
    cout << "缓存大小 = " << _capacity << endl;
}

bool Cache::isHaveElement(string & key)//判断是否有记录没问题
{
   auto it = _hashMap.find(key);
   if(it == _hashMap.end())
   {
       return false;
   }
   return true;
}

string Cache::getElement(string & key)//获取没有问题
{
    auto it = _hashMap.find(key);
    if(it == _hashMap.end())
    {
        cout << "没有找到数据" << endl;
        return NULL;
    }
    else
    {
        cout << "找到了数据" << endl;
        string value = it->second->value;
        _cacheList.splice(_cacheList.begin(), _cacheList, it->second);
        _hashMap[key] = _cacheList.begin();
        return value;
    }
}

void Cache::addElement(const string & key, const string & value)
{
#if 1 //数据从查询写入没有问题
    cout << "数据写入缓存" << endl;
    cout << key << value << endl;
#endif

    auto it = _hashMap.find(key);
    if(it == _hashMap.end())
    {
        if((int)_cacheList.size() == _capacity)
        {
#if 1
            cout << "进行了淘汰" << endl;
            cout << "列表大小为 = " << _cacheList.size() << endl;
            cout << "capacity大小为 = " << _capacity << endl;
#endif
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

#if 1
    cout << "读取缓存内容" << endl;
    cout << "缓存文件名 = " << fileName << endl;
#endif

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
        iss >> key;
        iss >> value;
        CacheNode node(key, value);
        _cacheList.push_back(node);
        _hashMap.insert(make_pair(key, _cacheList.begin()));
    }

#if 1 //测试从文件写入缓存
    cout << "打印文件缓存内容" << endl;
    cout << _hashMap.size() << endl;
    cout << _cacheList.size() << endl;
    for(auto & elem : _cacheList)
    {
        cout << "key = " << elem.key <<  " " << endl
            << "value = " << elem.value << endl;
    }
#endif

}

void Cache::writeToFile(const string & fileName)
{

#if 0 //测试写入缓存数据
    cout << "测试需要写入文件的数据" << endl;
    //写的应该是_hasmap
    cout << _hashMap.size() << endl;
    cout << _cacheList.size() << endl;
    for(auto & elem : _cacheList)
    {
        cout << "key = " << elem.key;
        //读取有问题，每次读取的时候都有换行被读取
    }

#endif
    ofstream ofs(fileName);
        for(auto & elem : _cacheList)
        {
            ofs << elem.key << "      " << elem.value << endl;
        }
    ofs.close();
}

void Cache::update(const Cache & rhs)
{
    cout << "更新单个缓存数据" << endl;
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


