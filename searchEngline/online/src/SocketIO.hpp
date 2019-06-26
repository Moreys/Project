/*************************************************************************
  @FileName:  SocketIO.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 21时24分13秒
 ************************************************************************/
                                                                         
#ifndef __SOCKETIO_HPP__
#define __SOCKETIO_HPP__

namespace morey
{

class SocketIO
{
public:
    explicit
    SocketIO(int fd)
    : _fd(fd)
    {}
public:
    int readn(char * buff, int len);
    int readline(char * buff, int maxlen);
    int writen(const char * buff, int len);
private:
    int recvPeek(char * buff, int len);
private:
    int _fd;
};


}//end of namespace morey

#endif

