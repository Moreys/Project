/*************************************************************************
  @FileName:  Task.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月19日 星期三 10时53分56秒
 ************************************************************************/

#include "Task.hpp"
#include "Configuration.hpp"
#include "Dictionary.hpp"
#include "Cache.hpp"
#include "Thread.hpp"
#include "CacheManager.hpp"
#include "cJSON.hpp"
#include <string.h>
#include <algorithm>


namespace morey
{

Task::Task(const string & queryWord,const TcpConnectionPtr & conn)
: _queryWord(queryWord)
, _conn(conn)
    {
    }


//function:相应客户端的请求
bool Task::response(Cache & cache)
{
    if(cache.isHaveElement(_queryWord))
    {
        _conn->sendInLoop(cache.getElement(_queryWord));
        return true;
    }
    return false;
}
//function: 执行查询
void Task::execute()
{
#if 1
    Cache & cacheNode = (Singleton<CacheManager>::getInstance(
            Singleton<Configuration>::getInstance(PATH)->getCachePath()))
           ->getCache(tNumber);
    if(response(cacheNode))//先判断缓存中有没有，先匹配缓存中的数据，发现就直接返回
    {
        //TODO 从缓存中进行查找
        return;
    }
#endif
    else
    {
        queryIndexTable();
#if 0
        while(!_resultQue.empty())
        {
            _resultQue.pop();
        }
#endif
#if 1
        cJSON *root;
        root = cJSON_CreateArray();
        if(!root)
        {
            LogError("获取json头部失败");
        }
        if(8 < _resultQue.size())
        {
            int count =  _resultQue.size() - 4;
            for(int idx = 0; idx < count ; ++idx )
            {
                _resultQue.pop();
            }
        }
        while(!_resultQue.empty())
        {
            cJSON_AddItemToArray(root, cJSON_CreateString(
                                 _resultQue.top()._word.c_str()));
            cJSON_AddItemToArray(root, cJSON_CreateNumber(
                                 _resultQue.top()._iDist));
            //TODO 添加到缓存中
            _resultQue.pop();
        }
        string response = cJSON_PrintUnformatted(root);
        cacheNode.addElement(_queryWord, response);
#endif
        _conn->sendInLoop(response);
        cJSON_Delete(root);
    }
}

vector<Character> Task::getOneChareacter(const string & word)
{
    auto cit = word.begin();
    vector<Character> ret;
#if 0
    while(cit < word.end())
    {
        Character tmp(1, *cit);
        ret.push_back(tmp);
        cit++;
    }
#endif

#if 1
    while(cit < word.end())
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
#endif

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
#if 1
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
#endif 
#if 0 //测试后得到的set没有问题
    for(auto myChare : allRally)
    {
        cout << myChare << endl;
    }
#endif
    statistic(allRally); //读取跟候选词相近的放入到里面进行其他计算
}

//function: 进行计算
//args: iset: 根据单词首字母得到的索引多对应的所有单词
void Task::statistic(set<int> & iset)
{
    vector<pair<string, int>> dict = (Singleton<Dictionary>::getInstance(
            Singleton<Configuration>::getInstance(PATH)->getEnglishDic(),
            Singleton<Configuration>::getInstance(PATH)->getEnIndex()))->getDic();
    for(auto & idx : iset)
    {
        string key = dict[idx].first; //找到对应key 的下标
#if 0 //测试过获取key和value没有问题
        cout << "key = " <<  key << endl;
        cout << "value = " <<  dict[idx].second << endl;
#endif

#if 1
        int iDist  = distance(key); //计算最小编辑距离
        if(iDist <= 3)
        {
            Result res;
            res._word = key;
            res._iDist = iDist;
            res._iFreq = dict[idx].second;
            _resultQue.push(res); //满足条件的记录三个状态，进入队列
        }
#endif
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
    for(int i = 0; i <= len1; ++i)
    {
        edit[i][0] = i;
    }
    for(int i = 0; i <= len2; ++i)
    {
        edit[0][i] = i;
    }
    for(int i = 1; i <= len1; ++i)
    {
        for(int j = 1; j <= len2; ++j)
        {
            if(queryChara[i - 1] == indexChara[j - 1])
            {
                edit[i][j] = edit[i - 1][j - 1];
            }
            else
            {
                edit[i][j] = min(edit[i - 1][j - 1], min(edit[i - 1][j], edit[i][j - 1])) + 1;
            }
        }
    }
    return edit[len1][len2];
}


}//end of namespace morey

