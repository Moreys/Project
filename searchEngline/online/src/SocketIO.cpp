/*************************************************************************
  @FileName:  SocketIO.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 21时24分13秒
 ************************************************************************/

#include "SocketIO.hpp"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace morey
{

int SocketIO::readn(char * buff, int len)
{
    int left = len;
    char *p = buff;
    while(left > 0)
    {
        int ret = ::read(_fd, p, left);
        if(-1 == ret && errno == EINTR)
        {
            continue;
            return EXIT_FAILURE;
        }
        else if(-1 == ret)
        {
            perror("read");
            return len - left;
        }
        else if(0 == ret)
        {
            break;
        }
        p += ret;
        left -= ret;
    }
    return len - left;
}

int SocketIO::readline(char * buff, int maxlen)
{
    int left = maxlen - 1;
    char * p = buff;
    int ret;
    int total = 0;
    while(left > 0)
    {
        ret = recvPeek(p, left);
        for(int idx = 0; idx != ret; ++idx)
        {
            if(p[idx] == '\n')
            {
                int sz = idx + 1;
                if(readn(p, sz) != sz)
                    return EXIT_FAILURE;
                total += sz;
                p += sz;
                *p = '\0';
                return total;
            }
        }
        readn(p, ret);
        p += ret;
        left -= ret;
        total += ret;
    }
    *p = '\0';
    return maxlen - 1;
}

int SocketIO::writen(const char * buff, int len)
{
    int left = len;
    const char * p = buff;
    while(left > 0)
    {
        int ret = :: write(_fd, p, left);
        if(-1 == ret && EINTR == errno)
        {
            continue;
        }
        else if(-1 ==ret)
        {
            perror("write");
            return len - left;
        }
        else
        {
            left -= ret;
            p += ret;
        }
    }
    return len - left;
}

int SocketIO::recvPeek(char * buff, int len)
{
    int ret;
    do
    {
        ret = ::recv(_fd, buff, len, MSG_PEEK);
    }while(-1 == ret && errno == EINTR);
    return ret;
}

}//end of namespace morey


