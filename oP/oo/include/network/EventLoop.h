/*************************************************************************
  @FileName:  EventLoop.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Thu 13 Jun 2019 04:44:37 PM CST
 ************************************************************************/
                                                                         
#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include "MutexLock.hpp"

#include <sys/epoll.h>

#include <map>
#include <memory>
#include <vector>
#include <functional>
using std::map;
using std::vector;
using std::shared_ptr;

namespace morey
{

class Acceptor;
class TcpConnection;

class EventLoop
{
public:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
    using Functor = std::function<void()>;

    EventLoop(Acceptor & acceptor);
public:
    void loop();
    void unloop();
    void runInLoop(Functor && cb);
    void setConnectionCallback(TcpConnectionCallback && cb)
    { _onConnection = std::move(cb); }
    void setMessageCallback(TcpConnectionCallback && cb)
    { _onMessage = std::move(cb); }
    void setCloseCallback(TcpConnectionCallback && cb)
    { _onClose = std::move(cb); }
private:
    void waitEpollFd();
    void handleNewConnctone();
    void handleMessage(int fd);
    void handleRead();
    void wakeup();
    int createEpollFd();
    int createEventFd();
    void doPendingFunctors();

    void addEpollFdRead(int fd);
    void delEpoolFdRead(int fd);
    bool isConnectionClose(int fd);

private:
    int _efd;
    int _eventfd;
    Acceptor & _acceptor;
    vector<struct epoll_event> _eventList;
    map<int, TcpConnectionPtr> _conns;
    bool _isLooping;

    MutexLock _mutex;
    vector<Functor> _pendingFunctors;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

}//end of namespace morey

#endif

