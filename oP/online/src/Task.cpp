/*************************************************************************
  @FileName:  Task.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月19日 星期三 10时53分56秒
 ************************************************************************/

#include "Task.hpp"
#include "Configuration.hpp"
#include "Dictionary.hpp"
#include <string.h>
#include <algorithm>


namespace morey
{

Task::Task(const string & queryWord,const TcpConnectionPtr & conn)
    : _queryWord(queryWord)
      , _conn(conn)
    {
    }

//function: 执行查询
void Task::execute()
{
    //执行查询的各项操作，最后封装结果返回给客户端
    string response = _queryWord;
    _conn->sendInLoop(response);

}

vector<Character> Task::getOneChareacter(const string & word)
{
    auto cit = word.begin();
    vector<Character> ret;
    while(cit<word.end())
    {
        if(224 == (*cit & 224))
        {
            Character temp;
            temp.append(cit, cit + 3);
            ret.push_back(temp);
            cit = cit + 3;
        }
        else if(240 == (*cit & 240))
        {
            Character tmp;
            tmp.append(cit, cit + 4);
            ret.push_back(tmp);
            cit = cit + 4;
        }
        else
        {
            Character tmp(1, *cit);
            ret.push_back(tmp);
            cit++;
        }
    }
    return ret;
}

//function： 查询索引
void Task::queryIndexTable()
{
    map<string, set<int>> index = (Singleton<Dictionary>::getInstance(
              Singleton<Configuration>::getInstance(PATH)->getEnglishDic(),
              Singleton<Configuration>::getInstance(PATH)->getEnIndex()))->getIndex();

    vector<Character> oneChareacter = getOneChareacter(_queryWord);
    set<int>allRally;
    for(auto myChare : oneChareacter)
    {
        auto cit = index.find(myChare);
        if(cit != index.end())
        {
            for(auto & idx : cit->second)
            {
                allRally.insert(idx);
            }
        }
    }
    statistic(allRally); //读取跟候选词相近的放入到里面进行其他计算
}

//function: 进行计算
void Task::statistic(set<int> & iset)
{
    vector<pair<string, int>> dict = (Singleton<Dictionary>::getInstance(
              Singleton<Configuration>::getInstance(PATH)->getEnglishDic(),
              Singleton<Configuration>::getInstance(PATH)->getEnIndex()))->getDic();
    for(auto & idx : iset)
    {
        string key = dict[idx].first;
        int iDist  = distance(key); //计算最小编辑距离
        if(iDist <= 3)
        {
            Result res;
            res._word = key;
            res._iDist = iDist;
            res._iFreq = dict[idx].second;
            _resultQue.push(res); //满足条件的记录三个状态，进入队列
        }
    }
}

//function: 计算最小编辑距离
int Task::distance(const string & rhs)
{
    vector<Character> queryChara = getOneChareacter(_queryWord);
    vector<Character> indexChara = getOneChareacter(rhs);

    int len1, len2;
    len1 = queryChara.size();
    len2 = indexChara.size();
    int edit[len1 + 1][len2 + 1];
    int i, j;
    for(i = 0; i < len1; ++i)
    {
        for(j = 0; j < len2; ++j)
        {
            edit[i][j] = 0;
        }
    }
    for(i=0;i<len1;++i)
    {
        edit[i][0]=i;
    }
    for(j=0;j<=len2;++j)
    {
        edit[0][j]=j;
    }
    for(i = 1; i < len1; ++i)
    {
        for(j = 1; j < len2; ++j)
        {
            int cost = ((queryChara[i - 1] == indexChara[j - 1] ? 0 : 1));
            int deletion = edit[i - 1][j] + 1;
            int insertion = edit[i][j - 1] + 1;
            int substitution = edit[i - 1][j - 1] + cost;
            edit[i][j] = min(deletion, min(insertion,substitution));
        }
    }
    return edit[len1][len2];
}

//function:相应客户端的请求
void Task::response(Cache & cache)
{
    
}

}//end of namespace morey

