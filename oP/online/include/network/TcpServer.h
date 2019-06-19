/*************************************************************************
  @FileName:  TcpServer.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Thu 13 Jun 2019 09:31:53 PM CST
 ************************************************************************/
                                                                         
#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"

namespace morey
{
//一个智能指针，一个回调函数
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;

class TcpServer
{
public:
    TcpServer(const string & ip, unsigned short port);
public:
    void start();

    //三个方法，参数是TcpConnection类型的回调函数
    void setConnectionCallback(TcpConnectionCallback && cb);
    void setMessageCallback(TcpConnectionCallback && cb);
    void setCloseCallback(TcpConnectionCallback && cb);

private:
    Acceptor _acceptor;
    EventLoop _loop;

};

}//end of namespace morey

#endif


