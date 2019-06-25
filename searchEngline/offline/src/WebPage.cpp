/*************************************************************************
  @FileName:  WebPage.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 21时18分32秒
 ************************************************************************/

#include "WebPage.hpp"

#include <stdlib.h>
#include <iostream>
#include <queue>
#include <algorithm>
using std::endl;
using std::cout;
using std::priority_queue;
using std::pair;
using std::make_pair;

namespace morey
{

struct WordFreqCompare
{
    bool operator()(const pair<string, int> & left, const pair<string,int> & right)
    {
        if(left.second < right.second)
        {
            return true;
        }
        else if(left.second == right.second && 
                left.first > right.first)
        {
            return  true;
        }
        else 
        {
            return false;
        }
    }
};

WebPage::WebPage(string & doc, Configuration & config, Segmentation & jieba)
: _doc(doc)
{
    _topWords.reserve(10);
    processDoc(doc, config, jieba);
}

int WebPage::getDocId()
{

}

string WebPage::getDoc()
{

}

map<string, int> & WebPage::getWordsMap()
{

}
bool operator==(const WebPage & lhs, const WebPage & rhs)
{

}
bool operator<(const WebPage & lhs, const WebPage & rhs)
{

}
void WebPage::processDoc(const string & doc, Configuration & config, Segmentation &)
{

}
void WebPage::calcTopK(vector<string> & woedsVec, int k , set<string> & stopWordList)
{

}

}//end of namespace morey


