/*************************************************************************
  @FileName:  PageLib.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 17时12分57秒
 ************************************************************************/
                                                                         
#ifndef __PAGELIB_HPP__
#define __PAGELIB_HPP__

#include <vector>
#include <string>


namespace morey
{
class Configuration;
class DirScanner;
class PageLib
{
public:
    PageLib(Configuration & conf, DirScanner & dirScanner);
    void create();
    void store();

private:
    Configuration & _conf;
    DirScanner & _dirScanner;
    std::vector<std::string> _vecFiles;
};

}//end if namespace morey

#endif

