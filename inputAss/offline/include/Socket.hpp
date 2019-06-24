/*************************************************************************
  @FileName:  Socket.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 21时16分17秒
 ************************************************************************/
                                                                         
#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__
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

