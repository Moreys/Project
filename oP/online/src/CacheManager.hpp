/*************************************************************************
  @FileName:  CacheManager.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月20日 星期四 15时07分49秒
 ************************************************************************/
                                                                         
#ifndef __CACHEMANAGER_HPP_
#define __CACHEMANAGER_HPP_

#include <vector>
#include <iostream>
#include <string>

using std::string;
using std::vector;
namespace morey
{
class Cache;
class CacheManager
{
public:
    CacheManager(const string & fileName);

public:
    static void initCahche(const string & fileName);
    static Cache & getCache(size_t idx);
    static void periodicUpdateCache();

private:
    static string _cachePath;
    static vector<Cache> _cacheNumber;
};
}//end of namespace morey

#endif

