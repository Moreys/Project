/*************************************************************************
  @FileName:  Socket.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 21时16分17秒
 ************************************************************************/

#include "Socket.hpp"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace morey
{
Socket::Socket()
{
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == _fd)
    {
        perror("socket");
    }
}
Socket::Socket(int fd)
: _fd(fd)
{}

Socket::~Socket()
{
    ::close(_fd);
}

int Socket::fd() const
{
    return _fd;
}

void Socket::shutdownWrite()
{
    ::shutdown(_fd, SHUT_WR);
}

}//end of namespace morey


