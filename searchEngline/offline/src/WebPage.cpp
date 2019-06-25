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

//function:获取文档id
int WebPage::getDocId()
{
   return _docID; 
}

//function:获取文档
string WebPage::getDoc()
{
    return _doc;
}

//function: 获取文档的词频统计
map<string, int> & WebPage::getWordsMap()
{
    return _wordsMap;
}

//function: 判断两篇文章是否相等
bool operator==(const WebPage & lhs, const WebPage & rhs)
{
    int commNum = 0;
    auto lIter = lhs._topWords.begin();
    for(; lIter != lhs._topWords.end(); ++lIter)
    {
        commNum += std::count(rhs._topWords.begin(), rhs._topWords.end(), *lIter);
    }
    int lhsNum = lhs._topWords.size();
    int rhsNum = rhs._topWords.size();
    int totalNum = lhsNum < rhsNum ? lhsNum : rhsNum;
    if(static_cast<double>(commNum) / totalNum > 0.75)
    {
        return  true;
    }
    else
    {
        return false;
    }
}

//function: 对文档Docid进行排序
bool operator<(const WebPage & lhs, const WebPage & rhs)
{
    if(lhs._docID < rhs._docID)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//function: 对格式化文档进行处理，对一篇文章进行处理
void WebPage::processDoc(const string & doc, Configuration & config, Segmentation & jieba)
{
    string docIdHead = "<docid>";
    string docIdTail = "</docid>";
    string docUrlHead = "<link>";
    string docUrlTail = "</link>";
    string docTitleHead = "<title>";
    string docTitleTail = "</title>";
    string docContentHead = "<content>";
    string docContentTail = "</content>";

    int bpos = doc.find(docIdHead);
    int epos = doc.find(docIdTail);
    string docId = doc.substr(bpos + docIdHead.size(), epos - bpos - docIdHead.size());
    //substr 根据一个长串，返回长串内的指定字串
    //参数1 开始位置，参数2取几个字符
    //返回:想要获取的字串。
    _docID = stoi(docId);
    bpos = doc.find(docTitleHead);
    epos = doc.find(docTitleTail);
    string docTitle = doc.substr(bpos + docTitleHead.size(),
                                 epos - bpos - docTitleHead.size());
    _docTitle = docTitle;
    
    bpos = doc.find(docContentHead);
    epos = doc.find(docContentTail);
    string docContent = doc.substr(bpos + docContentHead.size(),
                                 epos - bpos - docContentHead.size());
    _docContent = docContent;

    vector<string> wordsVec = jieba(_docContent.c_str());
    set<string> & stopWordList = config.getStopWordList();
    calcTopK(wordsVec, TOPK_NUMBER, stopWordList);
}

//function:获取文档的topk词集 提取top关键词，如果关键词有N个相同则认为是同一篇文章
//args: woedsVec:分词的结果; k:词频最高个数   stopWordList:停用词
void WebPage::calcTopK(vector<string> & wordsVec, int k , set<string> & stopWordList)
{
    for(auto idx = wordsVec.begin(); idx != wordsVec.end(); ++idx)
    {
        auto swl = stopWordList.find(*idx);
        if(swl == stopWordList.end())
        {
            ++_wordsMap[*idx];
        }
    }
    priority_queue<pair<string, int>, vector<pair<string, int>>, WordFreqCompare> 
        wordFreqQue(_wordsMap.begin(), _wordsMap.end()); //将map的内容放入到自动队列进行按规则进行排序

    while(!wordFreqQue.empty())
    {
        string top = wordFreqQue.top().first;
        wordFreqQue.pop();
        if(top.size() == 1 && (static_cast<unsigned int>(top[0]) == 10 ||
                                static_cast<unsigned int>(top[0]) == 13))
        {
            continue;
        }
        _topWords.push_back(top);
        if(_topWords.size() >= static_cast<size_t>(k))
        {
            break;
        }
    }
#if 0
    for(auto & elem : _wordsMap)
    {
        cout << elem.first << "   " << elem.second << endl;
    }
    for(auto & elem : _topWords)
    {
        cout << elem << "    " << elem.size() << "   " 
            << static_cast<unsigned int>(elem[0]) << endl;
    }
#endif
}

}//end of namespace morey


