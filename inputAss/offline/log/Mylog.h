#ifndef __MYLOG_H__
#define __MYLOG_H__
#include <log4cpp/Category.hh>

#include <string>

using std::string;

using namespace log4cpp;

#define  prefix(msg) string("[").append(__FILE__)\
                .append(":").append(__FUNCTION__)\
                .append(":").append(std::to_string(__LINE__)).append("]")\
                .append(msg)
namespace morey
{

class  Mylogger
{
public:
    static Mylogger * getInstance()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
            Category::shutdown();
        }
    }
    Category & categoryInit();

    void warn(const char * msg);

    template<typename... Args>
    void warn(Args... args)
    {
        _myCategory.warn(args...);
    }

    void error(const char * msg);

    template<typename... Args>
    void error(Args... args)
    {
        _myCategory.error(args...);
    }

    void debug(const char * msg);

    template<typename... Args>
    void debug(Args... args)
    {
        _myCategory.debug(args...);
    }

    
    void info(const char * msg);

    template<typename... Args>
    void info(Args... args)
    {       
        _myCategory.info(args...);
    }
private:
    Mylogger();
    ~Mylogger();
private:
    static Mylogger * _pInstance;
    Category & _myCategory;
};
}//end of namespace morey
#define LogError(msg,...) morey::Mylogger::getInstance()->error(prefix(msg).c_str(),##__VA_ARGS__)
#define LogInfo(msg,...) morey::Mylogger::getInstance()->info(prefix(msg).c_str(),##__VA_ARGS__)
#define LogWarn(msg,...) morey::Mylogger::getInstance()->warn(prefix(msg).c_str(),##__VA_ARGS__)
#define LogDebug(msg,...) morey::Mylogger::getInstance()->debug(prefix(msg).c_str(),##__VA_ARGS__)

#endif
