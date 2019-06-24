/*************************************************************************
  @FileName:  Configuration.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月15日 星期六 17时33分33秒
 ************************************************************************/

#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__
#include "Noncopyable.hpp"

#include <string>
#include <map>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::map;

#define PATH "/root/project/inputAss/online/conf/dicq.conf"

namespace morey
{

class Configuration
: Noncopyable
{
public:
    Configuration(const string & filePath);
    map<string, string> & getConfigMap();
    void readConfiguration();
    void debug();
    string getFilepath()
    {
        return _filepath;
    }
public:
    string getIp() const;
    unsigned short getPort() const;
    string getEnDic() const;
    string getCnDic() const;
    string getEnIdx() const;
    string getCnIdx() const;
    string getCachePath() const;
private:
    string _filepath;
    map<string, string> _configMap;
};

template<typename Type>
class Singleton
{
    class AutoRelease
    {
    public:
        AutoRelease()
        {   cout << "AutoRelease()" << endl;      }

        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;   
            if(_pInstance)
                delete _pInstance;

        }

    };

public:
template<typename Type1, typename...Args>
static Type* getInstance(Type1 t2, Args ...args)
{
    if(nullptr == _pInstance)
    {
        _pInstance = new Type(t2, args...);
        (void)_autoRelease;
    }
    return _pInstance;
}

static void destroy()
{
    if(_pInstance)
        delete _pInstance;
}

private:
Singleton() {   cout << "Singleton()" << endl;   }
~Singleton() {  cout << "~Singleton()" << endl;  }
friend class AutoRelease;
private:
static Type * _pInstance;
static AutoRelease _autoRelease;

};

template<typename Type>
typename Singleton<Type>::AutoRelease Singleton<Type>::_autoRelease;

template<typename Type>
Type * Singleton<Type>::_pInstance = nullptr;//end of namespace morey

}//end of namespace morey
#endif

