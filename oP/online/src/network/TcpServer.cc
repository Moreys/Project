/*************************************************************************
  @FileName:  TcpServer.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Thu 13 Jun 2019 09:31:53 PM CST
 ************************************************************************/
                                                                         
#include "TcpServer.h"

namespace morey
{

TcpServer::TcpServer(const string & ip, unsigned short port)
: _acceptor(ip, port)
, _loop(_acceptor)
{}

void TcpServer::start()
{
    _acceptor.ready();
    _loop.loop();
}

    //三个方法，参数是TcpConnection类型的回调函数
void TcpServer::setConnectionCallback(TcpConnectionCallback && cb)
{
    _loop.setConnectionCallback(std::move(cb));
}
void TcpServer::setMessageCallback(TcpConnectionCallback && cb)
{
    _loop.setMessageCallback(std::move(cb));
}
void TcpServer::setCloseCallback(TcpConnectionCallback && cb)
{
    _loop.setCloseCallback(std::move(cb));
}

}//end of namespace morey



