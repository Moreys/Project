/*************************************************************************
  @FileName:  EventLoop.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Thu 13 Jun 2019 04:44:37 PM CST
 ************************************************************************/
                                                                         
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <assert.h>
#include <sys/eventfd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace morey
{


EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollFd())
, _eventfd(createEventFd())
, _acceptor(acceptor)
, _eventList(1024)
, _isLooping(false)
{
    addEpollFdRead(_acceptor.fd());
    addEpollFdRead(_eventfd);
}

//function: 循环监听
void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping)
    {
        waitEpollFd();
    }
}

//function: 退出循环监听
void EventLoop::unloop()
{
    if(_isLooping)
        _isLooping = false;
}

//function: 时间循环，将需要处理的事件放入到容器
void EventLoop::runInLoop(Functor && cb)
{
    {
        MutexLockGuard autolock(_mutex);
        _pendingFunctors.push_back(std::move(cb));
    }
    wakeup();
}

//function: 等待fd的接入，并分发fd
void EventLoop::waitEpollFd()
{
    int nready;
    do{
        nready = epoll_wait(_efd, &*_eventList.begin(), _eventList.size(), 5000);
    }while(-1 == nready && errno == EINTR);

    if(-1 == nready)
    {
        perror("epoll_wait");
        return;
    }
    else if(0 == nready)
    {
        cout << ">> epoll_wait timeout!" << endl;
    }
    else
    {
        if(nready == (int)_eventList.size())
        {
            _eventList.resize(2 * nready);
        }
        for(int idx = 0; idx != nready; ++idx)
        {
            int fd = _eventList[idx].data.fd;
            if(fd == _acceptor.fd()) //处理新连接
            {
                if(_eventList[idx].events & EPOLLIN)
                {
                    handleNewConnctone();
                }
            }
            else if(fd == _eventfd)
            {
                if(_eventList[idx].events & EPOLLIN)
                {
                    handleRead();
                    cout << "开始循环发送数据" << endl;
                    doPendingFunctors(); //在这里发送数据
                    cout << "循环发送数据结束" << endl;
                }
            }
            else //处理消息
            {
                if(_eventList[idx].events & EPOLLIN)
                {
                    handleMessage(fd);
                }
            }
        }
    }
}

//function: 处理新连接
void EventLoop::handleNewConnctone()
{
    int peerfd = _acceptor.accept();
    addEpollFdRead(peerfd);
    TcpConnectionPtr conn(new TcpConnection(peerfd, this));
    conn->setConnectionCallback(_onConnection);
    conn->setMessageCallback(_onMessage);
    conn->setCloseCallback(_onClose);

    _conns.insert(std::make_pair(peerfd, conn));

    conn->handleConnectionCallback();
}

//function: 处理消息
//正常处理和非正常处理
void EventLoop::handleMessage(int fd)
{
    bool isClosed = isConnectionClose(fd);
    auto iter = _conns.find(fd);
    assert(iter != _conns.end());//运行时断开
    
    if(!isClosed)
    {
        iter->second->handleMessageCallback();
    }
    else
    {
        delEpoolFdRead(fd);
        iter->second->handleCloseCallback();
        _conns.erase(iter);
    }
}

//function: 处理读取
void EventLoop::handleRead()
{
    uint64_t howmany;
    int ret = ::read(_eventfd, &howmany, sizeof(howmany));
    if(ret != sizeof(howmany))
    {
        perror("read");
    }
}

//function: 计时器，唤醒子线程
void EventLoop::wakeup()
{
    uint64_t one = 1;
    int ret = ::write(_eventfd, &one, sizeof(one));
    if(ret != sizeof(one))
    {
        perror("write");
    }
}

//function: 外处理的事件，在等待 
void EventLoop::doPendingFunctors()
{
    vector<Functor> tmp;
    {
        MutexLockGuard autolock(_mutex);
        tmp.swap(_pendingFunctors);//交换一下，给子线程进行处理
    }
    for(auto & functor : tmp)
    {
        functor(); //
    }
}

//function: 创建epoll
//return: ret: epoll_create1的返回值
int EventLoop::createEpollFd()
{
    int ret = ::epoll_create1(0);
    if(-1 == ret)
    {
        perror("epoll_create1");
    }
    return ret;
}

int EventLoop::createEventFd()
{
    int ret = ::eventfd(0, 0);
    if(-1 == ret)
    {
        perror("eventfd");
    }
    return ret;
}

//function:添加监听
void EventLoop::addEpollFdRead(int fd)
{
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;
    int ret = epoll_ctl(_efd, EPOLL_CTL_ADD, fd, &evt);
    if(-1 == ret){
        perror("epoll_ctl");
    }
}

//function: 删除监听事件
void EventLoop::delEpoolFdRead(int fd)
{
    struct epoll_event evt;
    evt.data.fd = fd;
    int ret = epoll_ctl(_efd, EPOLL_CTL_DEL, fd, &evt);
    if(-1 == ret){
        perror("epoll_ctl");
    }

}

//function:判断事件是否完成
//reutrn: ret: ret==0 表示读完了
bool EventLoop::isConnectionClose(int fd)
{
    int ret;
    do{
        char buff[1024];
        ret = recv(fd, buff, sizeof(buff), MSG_PEEK);
    }while(-1 == ret && errno == EINTR);
    return (ret == 0);
}


}//end of namespace morey


