/*************************************************************************
  @FileName:  PageLibPreprocessor.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 22时13分27秒
 ************************************************************************/
                                                                         
#ifndef __PAGELIBPREPROCESSOR_HPP__
#define __PAGELIBPREPROCESSOR_HPP__
#include "Segmentation.hpp"
#include "WebPage.hpp"

#include <vector>
#include <unordered_map>
using namespace std;

namespace morey
{
class PageLibPreprocessor
{
public:
    PageLibPreprocessor(Configuration & conf);
    void doProcess();
    
private:
    void readInfoFromFile();
    void cutRedundantPages();
    void buildInvertIdxTable();
    void storeOnDisk();

private:
    Configuration & _conf;
    Segmentation _jieba;
    std::vector<WebPage> _pageLib;//网页库容器对象
    std::unordered_map<int, std::pair<int, int>> _offsetLib; //偏移库对象
    std::unordered_map<string, std::vector<std::pair<int, double>>> _invertIdxTable; //单排索引表
};


}//end of namespace morey

#endif

