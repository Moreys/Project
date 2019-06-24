#include "Mylog.h"

#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>

#include <iostream>
using std::cout;
using std::endl;

namespace morey
{
Mylogger * Mylogger::_pInstance = nullptr;

Mylogger::Mylogger() : _myCategory(Category::getRoot().getInstance("mylogger"))
{
    PatternLayout *pLayout1 = new PatternLayout();
    pLayout1->setConversionPattern("%d: %p %c %x : %m%n");

    PatternLayout *pLayout2 = new PatternLayout();
    pLayout2->setConversionPattern("%d: %p %c %x : %m%n");

    OstreamAppender *pOstreamAppender = new OstreamAppender("pOstreamAppender", &cout);
    pOstreamAppender->setLayout(pLayout1);

    FileAppender * pFileAppender = new FileAppender("pFileAppender","Long.log");
    pFileAppender->setLayout(pLayout2);

    _myCategory.setAppender(pOstreamAppender);
    _myCategory.setAppender(pFileAppender);
    _myCategory.setPriority(Priority::DEBUG);
    cout << "Mylogger()" << endl;
}
Mylogger::~Mylogger()
{
    Category::shutdown();
    cout << "~Mylogger()" << endl;
}
void Mylogger::warn(const char * msg)
{
    _myCategory.warn(msg);
}
void Mylogger::info(const char * msg)
{
    _myCategory.info(msg);
}
void Mylogger::debug(const char * msg)
{
    _myCategory.debug(msg);
}

void Mylogger::error(const char *msg)
{
    _myCategory.error(msg);
}
}//end of namespace morey
