/*************************************************************************
  @FileName:  WebPage.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 21时18分32秒
 ************************************************************************/
                                                                         
#ifndef __WEBPAGE_HPP__
#define __WEBPAGE_HPP__
#include "Configuration.hpp"
#include "Segmentation.hpp"

#include <vector>
#include <map>
#include <set>
#include <vector>
using std::string;
using std::vector;
using std::map;
using std::set;

namespace morey
{

class WebPage
{
public:
    const static int TOPK_NUMBER = 20;
    WebPage(string & doc, Configuration & config, Segmentation & jieba);
    int getDocId();
    string getDoc();
    map<string, int> & getWordsMap();
friend bool operator==(const WebPage & lhs, const WebPage & rhs);
friend bool operator<(const WebPage & lhs, const WebPage & rhs);
private:
    void processDoc(const string & doc, Configuration & config, Segmentation &);
    void calcTopK(vector<string> & wordsVec, int k , set<string> & stopWordList);
private:
    string _doc;
    int _docID;
    string _docTitle;
    string _docUrl;
    string _docContent;
    string _docSummary;//文档摘要

    vector<string> _topWords; //词频最高的前20个词
    map<string, int> _wordsMap;//保存每篇文章的所有词语和词频，不含停用词
};

}//end of namespace morey

#endif

