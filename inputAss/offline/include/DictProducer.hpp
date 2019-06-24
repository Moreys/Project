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
#include <unordered_map>
#include <set>
#include <memory>

using std::string;
using std::vector;
using std::unordered_map;
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
    void build_enDict();
    void build_cn_dict();
    void build_enIndex();
    void build_cnIndex();
    void reand_endict();
    void reand_cndict();
    void init();
    void show_file() const;
    void show_dict() const;
    vector<string> getOneChareacter( const string & word);
    
private:
    void get_files();
    void push_endict();
    void push_cndict();
    void push_enIndex();
    void push_cnIndex();
    void pushIdxDict();
private:
    string _dir;
    vector<string> _files;
    vector<std::pair<string, int>> _cnIdx;
    vector<std::pair<string, int>> _enIdx;
    map<string, int> _endict;
    map<string, int> _cndict;
    unordered_map<string, set< int>> _enMapIdx;
    unordered_map<string, set< int>> _cnMapIdx;

    Dictionary  _dictionary;
    Configuration _config;
//    SplitTool * splitTool;
};

}//end of namespace morey

#endif

