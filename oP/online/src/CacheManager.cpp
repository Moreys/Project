/*************************************************************************
  @FileName:  CacheManager.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月20日 星期四 15时07分49秒
 ************************************************************************/

#include "CacheManager.hpp"
#include "Cache.hpp"

#define  PNUM  4

namespace morey
{

CacheManager::CacheManager(const string & fileName)
{
    _cachePath = fileName;
    initCahche(fileName);
}

void CacheManager::initCahche(const string & fileName)
{
    _cacheNumber.reserve(PNUM);
    Cache tmp(1000);
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


