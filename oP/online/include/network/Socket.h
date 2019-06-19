/*************************************************************************
  @FileName:  Socket.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Wed 12 Jun 2019 09:37:13 PM CST
 ************************************************************************/
                                                                         
#ifndef __SOCKET_H__
#define __SOCKET_H__


namespace morey
{

class Socket
{
public:
    Socket();
    explicit
    Socket(int fd);
    ~Socket();
public:
    int fd() const;
    void shutdownWrite();

private:
    int _fd;
};

}//end of namespace morey

#endif
