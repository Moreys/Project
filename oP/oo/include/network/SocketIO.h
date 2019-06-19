/*************************************************************************
  @FileName:  SocketIO.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Wed 12 Jun 2019 09:50:55 PM CST
 ************************************************************************/

#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

namespace morey
{
class SocketIO
{
public:
    explicit
    SocketIO(int fd);
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

