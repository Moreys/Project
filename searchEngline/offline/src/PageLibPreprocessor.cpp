/*************************************************************************
  @FileName:  PageLibPreprocessor.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 22时13分27秒
 ************************************************************************/

#include "PageLibPreprocessor.hpp"
#include "GlobalDefine.hpp"
#include "PageLib.hpp"
#include "Mylog.hpp"

#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::stringstream;

namespace morey
{

PageLibPreprocessor::
    PageLibPreprocessor(Configuration & conf)
    : _conf(conf)
{}

//function: 执行预处理
void PageLibPreprocessor::
doProcess()
{
    readInfoFromFile();
    time_t t1 = time(NULL);
    cutRedundantPages();
    buildInvertIdxTable();
    time_t t2 = time(NULL);
    cout << "网页去重复和网页倒排索引使用时间为: "
        << t1 - t2 << endl;
    storeOnDisk();    
}

//function: 根据配置信息读取网页库和网页偏移库的内容
void PageLibPreprocessor::
readInfoFromFile()
{
    map<string, string> fileMap = _conf.getConfigMap();
    string pageLibPath = fileMap[RIPEPAGELIB_KEY];
    string pageOffsetPath = fileMap[OFFSETLIB_KEY];
    ifstream ifsPage(pageLibPath.c_str());
    ifstream ifsOffset(pageOffsetPath.c_str());
    if(!ifsPage || !ifsOffset)
    {
        LogError("读取网页库和网页偏移库路径出错");
        return;
    }
    string line;
    int docId, docOffset, docLen;
    while(getline(ifsOffset, line))
    {
        stringstream ss(line);
        ss >> docId >> docOffset >> docLen;
        string doc;
        doc.resize(docLen, ' ');
        //resize 重新设置大小
        //参数一 需要设置的大小，参数二：初始化的内容
        ifsPage.seekg(docOffset, ifsPage.beg);
        ifsPage.read(&*doc.begin(), docLen);

        WebPage webPage(doc, _conf, _jieba);
        _pageLib.push_back(webPage);

       _offsetLib.insert(make_pair(docId, make_pair(docOffset, docLen)));
    }

#if 0
    for(auto & elem : _offsetLib)
    {
        cout << elem.first << "  " << elem.second.first
            << "   " << elem.second.second << endl;
    }
#endif

}

//function:对冗余网页进行去重
void PageLibPreprocessor::
cutRedundantPages()
{
   //循环遍历去重，判断是否相等，相等就从网页库中pop出来
   for(size_t i = 0 ; i != _pageLib.size() - 1; ++i)
   {
        for(size_t j = i + 1; j != _pageLib.size(); ++j)
        {
            if(_pageLib[i] == _pageLib[j])
            {
                _pageLib[j] = _pageLib[_pageLib.size() - 1];
                _pageLib.pop_back();
                --j; //比较位置进行交换
            }
        }
   }
}

//function: 创建倒排索引
void PageLibPreprocessor::
buildInvertIdxTable()
{
    // tf 在文章中出现次数、
    // df 某词在所有文章中出现的次数
    // idf ifd = log(N/df)   N为文档总数
    // 计算词的特征权重 w = tf * idf
    // 进行归一化处理 w’ = w / sqrt(w1^2 + w2^2 +...+ wn^2)
     
    for(auto & page : _pageLib)
    {
        map<string, int> & wordsMap = page.getWordsMap();
        for(auto & wordFreq : wordsMap)
        {
            _invertIdxTable[wordFreq.first].push_back(make_pair(
                                page.getDocId(), wordFreq.second));
        }
    }
    map<int, double> weightSum;

    int totalPageNum = _pageLib.size();
    for(auto & item : _invertIdxTable)
    {
        int df = item.second.size();
        double idf = long(static_cast<double>(totalPageNum) / df + 0.05) / log(2);
        for(auto & sitem : item.second)
        {
            double weight = sitem.second * idf;
            weightSum[sitem.first] += pow(weight, 2);
            sitem.second = weight;
        }
    }

    for(auto & item : _invertIdxTable)
    {
        for(auto & sitem : item.second)
        {
            sitem.second = sitem.second / sqrt(weightSum[sitem.first]);
        }
    }

#if 0
    for(auto & item : _invertIdxTable)
    {
        cout << item.first << "\t";
        for(auto & sitem : item.second)
        {
            cout << sitem.first << "   " << sitem.second << "   " ;
        }
        cout << endl;
    }
#endif
}

//function: 将处理后的网页库和网页偏离库以及倒排索引回写磁盘
void PageLibPreprocessor::
storeOnDisk()
{
    sort(_pageLib.begin(), _pageLib.end());
    //先回写新的网页偏移库；
    string newOffsetlib = (_conf.getConfigMap()[NEWOFFSETLIB_KEY].c_str());
    string newPageLib = (_conf.getConfigMap()[NEWPAGELIB_KEY].c_str());
    ofstream ofsNewOffset(newOffsetlib);
    ofstream ofsNewPageLib(newPageLib);
    if(!ofsNewOffset || !ofsNewPageLib)
    {
        LogError("回写网页偏移库路径错误");
    }
    for(auto & page : _pageLib)
    {
        int id = page.getDocId();
        int length = page.getDoc().size();
        ofstream::pos_type offset = ofsNewPageLib.tellp();
        ofsNewPageLib << page.getDoc();
        
        ofsNewOffset << id << '\t' << offset << '\t'
            << length << '\n';
    }

    ofsNewPageLib.close();
    ofsNewOffset.close();
    
    
    ofstream ofsInvertIdxTable(_conf.getConfigMap()[INVERTIDXLIB_KEY].c_str());
    for(auto & item : _invertIdxTable)
    {
        ofsInvertIdxTable << item.first << "\t";
        for(auto & sitem : item.second)
        {
            ofsInvertIdxTable << sitem.first << "\t" << sitem.second
                << "\t";
        }
        ofsInvertIdxTable << endl;
    }
    ofsInvertIdxTable.close();
}   

}//end of namespace morey


