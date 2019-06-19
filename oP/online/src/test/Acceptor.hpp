/*************************************************************************
  @FileName:  Acceptor.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 21时58分13秒
 ************************************************************************/

#ifndef __ACCEPTOR_HPP__
#define __ACCEPTOR_HPP__
#include "InetAddress.hpp"
#include "Socket.hpp"

namespace morey
{

class Acceptor
{
public:
    Acceptor(unsigned short port);
    Acceptor(const string & ip, unsigned short port);

public:
    void ready();
    int accept();
    int fd() const;
private:
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void bind();
    void listen();

private:
    InetAddress _addr;
    Socket _listenSock;
};


}//end of namespace morey

#endif
                                                                         

