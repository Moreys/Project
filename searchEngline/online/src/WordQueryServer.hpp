/*************************************************************************
  @FileName:  WordQueryServer.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月25日 星期二 21时38分56秒
 ************************************************************************/
                                                                         
#ifndef __WORKQUERYSERVER_HPP__
#define __WORKQUERYSERVER_HPP__
#include "Configuration.hpp"
#include "WordQuery.hpp"
#include "Threadpool.hpp"
#include "TcpServer.hpp"

namespace morey
{

class WordQueryServer
{
public:
    WordQueryServer(const string & fileName);
    void start();

private:
    void onConnection(const TcpConnectionPtr & conn);
    void onMessage(const TcpConnectionPtr & conn);
    void onClose(const TcpConnectionPtr & conn);
    void doTaskThread(const TcpConnectionPtr & conn, const string & msg);

private:
    Configuration _conf;
    WordQuery _wordQuery;
    TcpServer _tcpServer;
    Threadpool _pool;
};

    
}//end of namespace morey

#endif

