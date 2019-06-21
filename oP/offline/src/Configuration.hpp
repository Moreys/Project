/*************************************************************************
  @FileName:  Configuration.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月15日 星期六 17时33分33秒
 ************************************************************************/
                                                                         
#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__


#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;

namespace morey
{
//class SplitToolCppJieba;
class Configuration
{
public:
    Configuration(const string & filepath);
    map<string, string> & getConfigMap();
    void readConfiguration();
    void debug();
    string getFilepath()
    {
        return _filepath;
    }
    string getCnTxtPath();
    string getCnDicPath();
    string getcnFile();
    string getCnIdx();
    vector<string> & getCndictFile();
private:
    string _filepath;
    map<string, string> _configMap;
    vector<string> _cndictFile;
};


}//end of namespace morey

#endif

