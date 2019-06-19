/*************************************************************************
  @FileName:  Acceptor.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Wed 12 Jun 2019 10:39:55 PM CST
 ************************************************************************/
                                                                         
#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__
#include "InetAddress.h"
#include "Socket.h"


namespace morey
{

class Acceptor
{
public:
    Acceptor(unsigned short port);
    Acceptor(const string & ip, unsigned short port);

    void ready();
    int accept();
    int fd() const {return _listensock.fd(); }

private:
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void bind();
    void listen();

private:
    InetAddress _addr;
    Socket _listensock;
};

}//end of namespace morey

#endif

