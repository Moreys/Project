/*************************************************************************
  @FileName:  SocketIO.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Wed 12 Jun 2019 09:50:55 PM CST
 ************************************************************************/

#include "TcpConnection.hpp"
#include "InetAddress.hpp"
#include "EventLoop.hpp"
#include "Mylog.hpp"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include <sstream>
#include <iostream>
#include <string>
using namespace std;

namespace morey
{
TcpConnection::TcpConnection(int fd, EventLoop * loop)
: _sockfd(fd)
, _socketIO(fd)
, _localAddr(getLocalAddr(fd))
, _peerAddr(getPeerAddr(fd))
, _isShutdwonWrite(false)
, _loop(loop)
{
}

TcpConnection::~TcpConnection()
{
	if(!_isShutdwonWrite) {
		shutdown();
	}
}

string TcpConnection::receive()
{
	char buff[1024];
    memset(buff, 0, sizeof(buff));
    size_t ret = _socketIO.readline(buff, sizeof(buff));
    if(0 == ret)
    {
        return std::string();
    }
    else
    {
        return std::string(buff);
    }
#if 0 //处理得到的数据，由客户端处理，//这里有bug
    cout << "处理前收到的大小" << string(buff).size() << endl;    
    memcpy(buff1,buff,strlen(buff) -1);
    cout << "处理后收到的大小" << string(buff1).size() << endl;    
    cout << buff1 << endl;
    printf("%s", buff1);
    memcpy(buff1,buff,strlen(buff) -1);
#endif
}
	
void TcpConnection::send(const string & msg)
{
	_socketIO.writen(msg.c_str(), msg.size());
}
void TcpConnection::sendInLoop(const string & msg)
{
    _loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
}

void TcpConnection::shutdown()
{
	if(!_isShutdwonWrite) {
		_isShutdwonWrite = true;
		_sockfd.shutdownWrite();
	}
}

string TcpConnection::toString() const
{
	std::ostringstream oss;
	oss << _localAddr.ip() << ":" << _localAddr.port() << " --> "
		<< _peerAddr.ip() << ":" << _peerAddr.port();
	return oss.str();
}


InetAddress TcpConnection::getLocalAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	if(getsockname(_sockfd.fd(), (struct sockaddr*)&addr, &len) == -1)
    {
		perror("getsockname");
	}
	return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	if(getpeername(_sockfd.fd(), (struct sockaddr*)&addr, &len) == -1)
    {
		perror("getpeername");
	}
	return InetAddress(addr);
}

void TcpConnection::setConnectionCallback(const TcpConnectionCallback & cb)
{
	_onConnection = std::move(cb);
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback & cb)
{
	_onMessage = std::move(cb);
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback & cb)
{
	_onClose = std::move(cb);
}

void TcpConnection::handleConnectionCallback()
{
	if(_onConnection) {
		_onConnection(shared_from_this());
	}
}

void TcpConnection::handleMessageCallback()
{
	if(_onMessage) {
		_onMessage(shared_from_this());
	}
}

void TcpConnection::handleCloseCallback()
{
	if(_onClose) {
		_onClose(shared_from_this());
	}
}

}//end of namespace wd
