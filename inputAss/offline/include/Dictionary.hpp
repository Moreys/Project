/*************************************************************************
  @FileName:  Dictionary.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月17日 星期一 10时28分25秒
 ************************************************************************/
                                                                         
#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__

#include <set>
#include <map>
#include <string>
using std::map;
using std::string;
using std::set;

namespace morey
{

class Dictionary
{
public:
    void read(const string & filename);
    void store(const string & filename);
    void dispose(const string & filenameIfs,
                const string & filenameOfs);
    void getline();    

private:
    map<string, int> _count;
};

}//end of namespace morey

#endif


