/*************************************************************************
  @FileName:  WordQuery.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月25日 星期二 21时41分47秒
 ************************************************************************/

#ifndef __WORDQUERY_HPP__
#define __WORDQUERY_HPP__
#include "Configuration.hpp"
#include "Segmentation.hpp"
#include "WebPage.hpp"

#include <vector>
#include <set>
#include <map>
#include <string>

using std::unordered_map;
using std::vector;
using std::map;
using std::set;
using std::string;
using std::pair;

namespace morey
{

class WordQuery
{
public:
    WordQuery(Configuration &);
    string doQuery(const string & str);
void loadLibrary();

private:
vector<double> getQueryWordsWeightVector(vector<string> & queryWords);
bool executeQuery(const vector<string> & queryWords,
                             vector<pair<int,vector<double>>> & resultVec);
string createJson(vector<int> & docIdVec, const vector<string> & queryWords);
string returnNoAnswer();

private:
    Configuration & _conf;
    Segmentation _jieba;
    unordered_map<int, WebPage> _pageLib;
    unordered_map<int, pair<int, int>> _offsetLib;
    unordered_map<string, set<pair<int, double>>> _invertIdxTable;
};

}//end of namespace morey

#endif

