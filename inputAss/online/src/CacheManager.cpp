/*************************************************************************
  @FileName:  CacheManager.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月20日 星期四 15时07分49秒
 ************************************************************************/

#include "CacheManager.hpp"

#include <iostream>
using std::cout;
using std::endl;

#define  PNUM  4
namespace morey
{
CacheManager::CacheManager( string  fileName)
{
    _cachePath = fileName;
    initCahche(fileName);
#if 1
    cout << "CacheManager fileName = " << fileName << endl;
    cout << "初始化CacheManager" << endl;
#endif
}

void CacheManager::initCahche( string  fileName)
{
#if 0
    cout << "初始化缓存" << endl;
    cout << "CacheManager fileName = "<< fileName << endl;
#endif 
    _cacheNumber.reserve(PNUM);
    Cache tmp(10000);
    tmp.readFromFile(fileName);
    for(int i = 0; i < PNUM; ++i)
    {
        _cacheNumber.push_back(std::move(tmp));
    }
}

Cache & CacheManager::getCache(size_t idx)
{
    return _cacheNumber[idx];
}


void CacheManager::periodicUpdateCache()
{
    auto it = _cacheNumber.begin();
    Cache lastWrite = *(it++);
#if 1
    cout << "定时更新所有Cache" << endl;
#endif
    for(;it < _cacheNumber.end(); ++ it)
    {
        lastWrite.update(*it);
    }

    for(it = _cacheNumber.begin() + 1; it != _cacheNumber.end(); ++it)
    {
        (*it).update(lastWrite);
    }
    lastWrite.writeToFile(_cachePath);
}

}//end of namespace morey


