/*************************************************************************
  @FileName:  SpellcorrectServer.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 22时46分45秒
 ************************************************************************/

#include "SpellcorrectServer.hpp"
#include "Task.hpp"
#include "Mylog.hpp"

using std::endl;
using std::cout;

namespace morey
{

SpellcorrectServer::SpellcorrectServer( const string & ip,unsigned short port,
                                       size_t threadSize,size_t queSize)
                            : _tcpServer(ip, port)
                            , _pthreadpool(threadSize, queSize)
    {

    }


void SpellcorrectServer::start()
{
    _pthreadpool.start();
    LogInfo("服务器启动");
    _tcpServer.setConnectionCallback(bind(&SpellcorrectServer::onConnection,this, std::placeholders::_1));
    _tcpServer.setMessageCallback(bind(&SpellcorrectServer::onMessage, this, placeholders::_1));
    _tcpServer.setCloseCallback(bind(&SpellcorrectServer::onClose, this, placeholders::_1));
    _tcpServer.start();

}
void SpellcorrectServer::onConnection(TcpConnectionPtr conn)
{
    std::cout << conn->toString()
        << "连接服务器" << std::endl;
    conn->send("welcome to server.");
    LogInfo("%s, %s", conn->toString(),"连接服务器");
    
}
void SpellcorrectServer::onMessage(TcpConnectionPtr conn)
{
    string msg = conn->receive();
    std::cout << conn->toString()<< ">> 发送过来: " 
        << msg << endl;
    LogInfo("info, %s, %s, %s",conn->toString(), "发送了: ", msg);
    Task task(msg, conn);
   _pthreadpool.addTask(std::bind(&Task::execute, task)); 
}

void SpellcorrectServer::onClose(TcpConnectionPtr conn)
{
    cout << conn->toString() << ":已经退出" << endl;
}

}//end of namespace morey


