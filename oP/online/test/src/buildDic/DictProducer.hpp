/*************************************************************************
  @FileName:  DictProducer.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月15日 星期六 18时20分11秒
 ************************************************************************/
                                                                         
#ifndef __DICTPRODUCER_HPP__
#define __DICTPRODUCER_HPP__

#include "Dictionary.hpp"
#include "Configuration.hpp"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

using std::string;
using std::vector;
using std::map;
using std::set;

namespace morey
{

class SplitTool;

class DictProducer
{
public:
    DictProducer(const string & dir);
 //   DictProducer(const string & dir, SplitTool * splitTool);

public:
    void build_dict();
    void build_cn_dict();
    void build_index();
    void reand_dict();
    void init();
    void show_file() const;
    void show_dict() const;
private:
    void get_files();
    void push_dict();
private:
    string _dir;
    vector<string> _files;
    vector<std::pair<string, int>> _vecIdx;
    map<string, string> _dict;
    map<string, set< int>> _mapIdx;
    Dictionary  _dictionary;
    Configuration _config;
//    SplitTool * splitTool;
};

}//end of namespace morey

#endif

