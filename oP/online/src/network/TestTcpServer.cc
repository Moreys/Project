/*************************************************************************
  @FileName:  TestEventLoop.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Thu 13 Jun 2019 05:55:35 PM CST
 ************************************************************************/
                                                                         
#include "Threadpool.h"
#include "TcpServer.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

morey::Threadpool * gThreadpool = nullptr;

class Task
{
public:
    Task(const string & msg,
         const morey::TcpConnectionPtr & conn)
    : _msg(msg)
    , _conn(conn)
    {}

    //运行在线程池中的某一个子线程中
    void process()
    {
        string response = _msg;
        _conn->sendInLoop(response);
    }

private:
    string _msg;
    morey::TcpConnectionPtr _conn;
};

void onConnection(const morey::TcpConnectionPtr & conn)
{
    cout << conn->toString() << "has connected！" << endl;
    conn->send("welcome to server.");
}

void onMessage(const morey::TcpConnectionPtr & conn)
{
    //该回调函数的执行时间不宜过长  10ms
    cout << "onMessage..." << endl;
    string msg = conn->receive();
    cout << ">> receive msg from client:" << msg << endl;
    //业务处理交给
    //decode
    //compute
    //encode
    Task task(msg, conn);
    gThreadpool->addTask(std::bind(&Task::process, task)); 
}

void onClose(const morey::TcpConnectionPtr & conn)
{
    cout << "onClose..." << endl;
    cout << conn->toString() << "has closed!" << endl;
}

using namespace morey;
class EchoServer
{
public:
    void onConnection(const TcpConnectionPtr & conn);

};

int main()
{
    Threadpool threadpool(4, 10);
    threadpool.start();

    gThreadpool = &threadpool;

    morey::TcpServer server("172.17.42.252", 8989);

    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.setCloseCallback(onClose);

    server.start();
    return 0;
}

