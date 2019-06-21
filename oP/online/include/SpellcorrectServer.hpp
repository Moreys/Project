/*************************************************************************
  @FileName:  SpellcorrectServer.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 22时46分45秒
 ************************************************************************/
                                                                         
#ifndef __SPELLCORRECTSERVER_HPP__
#define __SPELLCORRECTSERVER_HPP__
#include "Configuration.hpp"
#include "TcpServer.hpp"
#include "Threadpool.hpp"

namespace morey
{

class SpellcorrectServer
{
public:
    SpellcorrectServer( const string & ip,
                       unsigned short port,
                       size_t threadSize,
                       size_t queSize);
    void start();
    void onConnection(TcpConnectionPtr conn);
    void onMessage(TcpConnectionPtr conn);
    void onClose(TcpConnectionPtr conn);
private:
    TcpServer _tcpServer;
    Threadpool _pthreadpool;
};

}//end of namespace morey

#endif

