/*************************************************************************
  @FileName:  Socket.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Wed 12 Jun 2019 09:37:13 PM CST
 ************************************************************************/

#include "Socket.h"

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
        perror("soket");
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

