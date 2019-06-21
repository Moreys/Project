/*************************************************************************
  @FileName:  InetAddress.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月18日 星期二 21时05分04秒
 ************************************************************************/
                                                                         
#ifndef __INETADDRESS_HPP__
#define __INETADDRESS_HPP__
#include <arpa/inet.h>
#include <string>
using std::string;

namespace morey
{

class InetAddress
{
public:
    explicit
    InetAddress(unsigned short port);
    InetAddress(const string & ip, unsigned short port);
    InetAddress(const struct sockaddr_in & addr);
public:
    string ip() const;
    unsigned short port() const;
    struct sockaddr_in * getInetAddressPtr() { return &_addr; }

private:
    struct sockaddr_in _addr;
};

}//end of namespace morey
#endif

