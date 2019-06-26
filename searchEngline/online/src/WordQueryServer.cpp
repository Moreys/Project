/*************************************************************************
  @FileName:  WordQueryServer.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月25日 星期二 21时38分56秒
 ************************************************************************/

#include "WordQueryServer.hpp"
#include "Mylog.hpp"

#include <stdio.h>
#include <string>
#include <functional>

namespace morey
{

WordQueryServer::WordQueryServer(const string & fileName)
:_conf(fileName)
, _wordQuery(_conf)
, _tcpServer("172.17.42.252", 8989)
, _pool(4, 10)
    {
        _tcpServer.setConnectionCallback(std::bind(& WordQueryServer::onConnection, this, cppjieba::placeholders::_1));
        _tcpServer.setMessageCallback(std::bind(& WordQueryServer::onMessage, this, cppjieba::placeholders::_1));
        _tcpServer.setCloseCallback(std::bind(& WordQueryServer::onClose, this, cppjieba::placeholders::_1));
    }

void WordQueryServer::start()
{
    _pool.start();
    _tcpServer.start();
}

void WordQueryServer::onConnection(const TcpConnectionPtr & conn)
{
    cout << conn->toString() << endl;
    LogInfo(conn->toString().c_str());
}

void WordQueryServer::onMessage(const TcpConnectionPtr & conn)
{
    string msg(conn->receive());
    size_t pos = msg.find('\n');
    msg = msg.substr(0, pos);
    cout << "client: " << msg << ", size :" << msg.size() << endl;
    _pool.addTask(std::bind(&WordQueryServer::doTaskThread, this, conn, msg));
}


void WordQueryServer::onClose(const TcpConnectionPtr & conn)
{
    cout << conn->toString() << endl;
}

void WordQueryServer::doTaskThread(const TcpConnectionPtr & conn, const string & msg)
{
    string ret = _wordQuery.doQuery(msg);
    int sz = ret.size();

    cout <<  "发送的大小为: " << sz << endl;
    string message(cppjieba::to_string(sz));
    message.append("\n").append(ret);

    cout << message << endl;
    conn->sendInLoop(message);

}

}//end of namespace morey


