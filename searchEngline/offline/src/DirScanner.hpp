/*************************************************************************
  @FileName:  DirScanner.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 15时47分09秒
 ************************************************************************/
                                                                         
#ifndef __DIRSCANNER_HPP__
#define __DIRSCANNER_HPP__

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace morey
{

const int kFileNo = 10000;
class Configuration;

class DirScanner
{
public:
    DirScanner(Configuration & conf);
    void operator()();
    std::vector<std::string>  & files();
    void debug();

private:
    void tarverse(const string & dirName);

private:
    std::vector<std::string> _vecFiles;
    Configuration & _conf;
};

}//end of namespace morey
#endif

