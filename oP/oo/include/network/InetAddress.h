/*************************************************************************
  @FileName:  InetAddress.h
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Wed 12 Jun 2019 09:12:06 PM CST
 ************************************************************************/
                                                                         
#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__
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
    struct sockaddr_in * getInetAddressPtr() { return &_addr;  }

private:
    struct sockaddr_in _addr;
};

}//end of namespace morey

#endif

