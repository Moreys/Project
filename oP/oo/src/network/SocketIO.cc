/*************************************************************************
  @FileName:  SocketIO.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Wed 12 Jun 2019 09:50:55 PM CST
 ************************************************************************/

#include "SocketIO.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>



namespace morey
{

SocketIO::SocketIO(int fd)
: _fd(fd)
{}

//function: 读取文件每次读取一个
//args: buff:缓冲区 ; len:长度
int SocketIO::readn(char * buff, int len)
{
    int left = len;
    char * p = buff;
    while(left > 0)
    {
        int ret = ::read(_fd, p, left);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("read");
            return len - left;
        }
        else if(0 == ret)
        {
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

//function: 读取文件每次读取一行
//args: buff:缓冲区 ; len:最大长度
//情况，一行读完了，一行没有读完，读取多行以后才读完
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
                readn(p, sz);
                total += sz;
                p += sz;
                *p = '\0';
                return total;
            }
        }
        //如果没有发现'\0'
        readn(p, ret);
        left -= ret;
        p += ret;
        total += ret;
    }
    *p = '\0';
    return total;
}

int SocketIO::writen(const char * buff, int len)
{
    int left = len;
    const char * p = buff;
    while(left > 0)
    {
        int ret = ::write(_fd, p, left);
        if(-1 == ret && EINTR == errno)
        {
            continue;
        }
        else if(-1 == ret)
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
    return  ret;
}


}//end of namespace morey


