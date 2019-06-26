/*************************************************************************
  @FileName:  WordQuery.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月25日 星期二 21时41分47秒
 ************************************************************************/

#include "WordQuery.hpp"
#include "Mylog.hpp"
#include "GlobalDefine.hpp"
#include "cJSON.hpp"


#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <json/json.h>

using namespace std;

struct SimilarityCompare 
{
    SimilarityCompare(vector<double> & base)
    : _base(base)
    {}

    bool operator()(const pair<int, vector<double>> & lhs,
                    const pair<int, vector<double>> & rhs)
    {
        double lhsCrossProdunct = 0;
        double rhsCrossProdunct = 0;
        double lhsVectorLength = 0;
        double rhsVectorLength = 0;
        for(int idx = 0; idx != (int)_base.size(); ++idx)
        {
            lhsCrossProdunct += (lhs.second)[idx] * _base[idx];
            rhsCrossProdunct += (rhs.second)[idx] * _base[idx];
            lhsVectorLength += pow((lhs.second)[idx], 2);
            rhsVectorLength += pow((lhs.second)[idx], 2);
        }
        if(lhsCrossProdunct / sqrt(lhsVectorLength) < rhsCrossProdunct / sqrt(rhsVectorLength))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    vector<double> _base;
};

namespace morey
{

WordQuery::WordQuery(Configuration & conf)
: _conf(conf)
{
    loadLibrary();
}

//function: 执行查询返回结果
string WordQuery::doQuery(const string & str)
{
    vector<string> queryWords;
    if(str.size() > 0)
    {
        queryWords = _jieba(str.c_str());
    }
    for(auto & item : queryWords)
    {
        cout <<item << endl;
        auto uit = _invertIdxTable.find(item);
        if(uit == _invertIdxTable.end())
        {
            cout << "没有找到" << item << endl;
            return returnNoAnswer();
        }
    }
    cout << endl;
    vector<double> weightList = getQueryWordsWeightVector(queryWords);
    SimilarityCompare similarityCmp(weightList);

    vector<pair<int, vector<double>>> resultVec;
    if(executeQuery(queryWords, resultVec))
    {
        stable_sort(resultVec.begin(), resultVec.end(), similarityCmp);
        vector<int> docIdVec;

        for(auto & item : resultVec)
        {
            docIdVec.push_back(item.first);
        }
        return createJson(docIdVec, queryWords);
    }
    else
    {
      return  returnNoAnswer();
    }
}

void WordQuery::loadLibrary()
{
    ifstream ifsPage(_conf.getConfigMap()[NEWPAGELIB_KEY].c_str());
    ifstream ifsOffset(_conf.getConfigMap()[NEWOFFSETLIB_KEY].c_str());
    if(!ifsPage || !ifsOffset)
    {
        LogError("读取库文件出错");
    }
    
    int docId, length, offset;
    string line;
    while(getline(ifsOffset, line))
    {
        cout << "开始读配置文件" << endl;
        stringstream ss(line);
        cout << line << endl;
        ss >> docId >> offset >> length;
        string doc;
        doc.resize(length, ' ');
        ifsPage.seekg(offset, ifsPage.beg);
        ifsPage.read(&*doc.begin(), length);

        WebPage webPage(doc, _conf, _jieba);
        _pageLib.insert(make_pair(docId, webPage));

        _offsetLib.insert(make_pair(docId, make_pair(offset, length)));
    }
    ifsPage.close();
    ifsOffset.close();
#if 0
    for(auto & elem : _offsetLib)
    {
        cout << elem.first << "  "
            << elem.second.first << " "
            << elem.second.second << endl;
    }
#endif
    ifstream ifsInventIdx(_conf.getConfigMap()[INVERTIDXLIB_KEY].c_str());
    if(!ifsInventIdx)
    {
        LogError("获取倒排索引路径错误");
    }
    string word;
    double weight;
    while(getline(ifsInventIdx, line))
    {
        stringstream ss(line);
        ss >> word;
        set<pair<int, double>> setID;
        while(ss >> docId >> weight)
        {
            setID.insert(make_pair(docId, weight));
        }
        _invertIdxTable.insert(make_pair(word, setID));
    }
    ifsInventIdx.close();
    cout << "loadLibrary() end" << endl;
}

//function: 计算查询词的权重值
vector<double> WordQuery::getQueryWordsWeightVector(vector<string> & queryWords)
{
    map<string, int> wordFregMap;
    for(auto  item : queryWords)
    {
        ++wordFregMap[item];
    }

    vector<double> weightList;
    double weightSum = 0;
    int totalPageNum = _offsetLib.size();

    for(auto & item : queryWords)
    {
        int df = _invertIdxTable[item].size();
        double idf = log(static_cast<double>(totalPageNum) / df + 0.05) / log(2);
        int tf = wordFregMap[item];
        double w = idf * tf;
        weightSum += pow(w, 2);
        weightList.push_back(w);
    }

    for(auto & item : weightList)
    {
        item /= sqrt(weightSum);
    }

    cout << "最后的权值为: " ;
    for(auto item : weightList)
    {
        cout << item << "\t";
    }
    cout << endl;
    return weightList;
}

//function: 执行查询
bool WordQuery::executeQuery(const vector<string> & queryWords,
                 vector<pair<int,vector<double>>> & resultVec)
{
    cout << "执行查询”" << endl;
    if(queryWords.size() == 0)
    {
        cout << "内容为空" << endl;
        return false;
    }
    typedef  set<pair<int, double>> :: iterator setIter;
    vector<pair<setIter, int>> iterVec;
    int minIterNum = 0x7FFFFFF;
    for(auto item : queryWords)
    {
        int sz = _invertIdxTable[item].size();
        if(sz == 0)
        {
            return false;
        }
        if(minIterNum > sz)
        {
            minIterNum = sz;
        }
        iterVec.push_back(make_pair(_invertIdxTable[item].begin(), 0));
    }
    cout << "miniItemNum: " << minIterNum << endl;
    
    bool isExiting = false;
    while(!isExiting)
    {
        int idx = 0;
        for(; idx != (int)iterVec.size() - 1; ++idx)
        {
            if((iterVec[idx].first)->first != iterVec[idx + 1].first->first)
                break;
        }
        if(idx == (int)iterVec.size() - 1)
        {
            vector<double> weightVec;
            int docId = iterVec[0].first->first;
            for(idx = 0; idx != (int)iterVec.size(); ++idx)
            {
                weightVec.push_back(iterVec[idx].first->second);
                ++(iterVec[idx].first);
                ++(iterVec[idx].second);
                if(iterVec[idx].second == minIterNum)
                {
                    isExiting = true;
                }
            }
            resultVec.push_back(make_pair(docId, weightVec));
        }
        else
        {
            int minDocId = 0x7FFFFFF;
            int iterIdx;
            for(idx = 0; idx != (int)iterVec.size(); ++idx)
            {
                if(iterVec[idx].first->first < minDocId)
                {
                    minDocId = iterVec[idx].first->first;
                    iterIdx = idx;
                }
            }
            ++(iterVec[iterIdx].first);
            ++(iterVec[iterIdx].second);
            if(iterVec[iterIdx].second == minIterNum)
            {
                isExiting = true;
            }
        }
    }
    return true;
}


//function: 封装json
string WordQuery::createJson(vector<int> & docIdVec,  const vector<string> & queryWords)
{
    Json::Value root;
    Json::Value arr;
    int cnt = 0;
    for(auto & id : docIdVec)
    {
        string summary = _pageLib[id].summary(queryWords);
        string title = _pageLib[id].getTitle();
        string url = _pageLib[id].getUrl();

        Json::Value elem;
        elem["title"] = title;
        elem["summary"] = summary;
        elem["url"] = url;
        arr.append(elem);
        if(++cnt == 100)
        {
            break;
        }
    }
    root["files"] = arr;
    Json::StyledWriter writer;
    return writer.write(root);
}

//function: 如果没有找到返回提示信息
string WordQuery::returnNoAnswer()
{
    Json::Value root;
    Json::Value arr;
    
    Json::Value elem;
    
    elem["title"] = "404没有找到";
    elem["summary"] = "没有找到需要的网页";
    elem["title"] = "";
    arr.append(elem);
    root["files"] = arr;
    Json::StyledWriter writer;
    return writer.write(root);
}

}//end of namespace morey


