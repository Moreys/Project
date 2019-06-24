/*************************************************************************
  @FileName:  Acceptor.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 21时58分13秒
 ************************************************************************/

#include "Acceptor.hpp"

namespace morey
{

Acceptor::Acceptor(unsigned short port)
: _addr(port)
, _listenSock()
{}

Acceptor::Acceptor(const string & ip, unsigned short port)
: _addr(ip, port)
, _listenSock()
{}

void Acceptor::ready()
{
    setReuseAddr(true);
    setReusePort(true);
    bind();
    listen();
}

int Acceptor::accept()
{
    int peerfd = ::accept(_listenSock.fd(), NULL, NULL);
    if(-1 == peerfd)
    {
        perror("accept");
    }
    return peerfd;
}

int Acceptor::fd() const
{
    return _listenSock.fd();    
}

void Acceptor::setReuseAddr(bool on)
{
    int one = on;
    if(setsockopt(_listenSock.fd(),
                  SOL_SOCKET,
                  SO_REUSEADDR,
                  &one,
                  sizeof(one)) < 0)
    {
        perror("setsockopt");
    }
}

void Acceptor::setReusePort(bool on)
{
    int one = on;
    if(setsockopt(_listenSock.fd(),
                  SOL_SOCKET,
                  SO_REUSEADDR,
                  &one,
                  sizeof(one)) < 0)
    {
        perror("setsockopt");
    }
}
void Acceptor::bind()
{
    int ret = ::bind(_listenSock.fd(), 
                     (struct sockaddr *)_addr.getInetAddressPtr(),
                     sizeof(struct sockaddr));
    if(-1 == ret)
    {
        perror("bind");
    }
}
void Acceptor::listen()
{
    int ret = ::listen(_listenSock.fd(), 10);
    if(-1 == ret)
    {
        perror("listen");
    }
}

}//end of namespace morey
