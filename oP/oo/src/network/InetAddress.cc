/*************************************************************************
  @FileName:  InetAddress.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      Wed 12 Jun 2019 09:17:15 PM CST
 ************************************************************************/

#include "InetAddress.h"
#include "string.h"

namespace morey
{

//function: 返回端口号
//args: prot:端口号
InetAddress::InetAddress(unsigned short port)
{
    ::memset(&_addr, 0, sizeof(struct sockaddr_in));    
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY;
}

//function: 设置ip跟端口
//args: ip:ip地址 ; port:端口号
InetAddress::InetAddress(const string & ip, unsigned short port)
{
    ::memset(&_addr, 0, sizeof(struct sockaddr_in));    
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

//function: IP地址相关的转换
//args: addr:sorckaddr_in参数设置
InetAddress::InetAddress(const struct sockaddr_in & addr)
: _addr(addr)
{}

//function: ip:地址
//return: string:addr
string InetAddress::ip() const
{
    return string(::inet_ntoa(_addr.sin_addr));
}

//function: 端口号
//return: port
unsigned short InetAddress::port() const
{
    return ntohs(_addr.sin_port);
}

}//end of namespace morey

