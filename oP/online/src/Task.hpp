/*************************************************************************
  @FileName:  Task.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月19日 星期三 10时53分56秒
 ************************************************************************/
                                                                         
#ifndef __TASK_HPP__
#define __TASK_HPP__
#include "Dictionary.hpp"
#include "TcpConnection.hpp"
#include "Configuration.hpp"
#include <string>
#include <vector>
#include <queue>
using std::string;


namespace morey
{

class Cache;

class Compare
{
public:
    bool operator()(const Result & lhs,const Result &rhs)
    {
        if(lhs._iDist != rhs._iDist)
            return lhs._iDist < rhs._iDist;
        else
            return lhs._iFreq > rhs._iFreq;
    }
};

using Character = string;
class Task
{
public:
    Task(const string & queryWord,const TcpConnectionPtr & conn);
    void execute();
private:
    void queryIndexTable();
    void statistic(set<int> & iset);
    int distance(const string & rhs);
    void response(Cache & cache);

    vector<Character>getOneChareacter(const string &);
private:
    string _queryWord;
    int _peerfd;
    TcpConnectionPtr _conn;
    priority_queue<Result, vector<Result>, Compare> _resultQue;
};

}//end of namespace morey

#endif

