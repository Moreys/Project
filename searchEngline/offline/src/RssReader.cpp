/*************************************************************************
  @FileName:  RssReader.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 17时30分54秒
 ************************************************************************/
#include "RssReader.hpp"                                                                         

#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
using std::cout;
using std::endl;
using std::ostringstream;
using std::ofstream;
using std::regex;

RssReader::RssReader(vector<string> &files)
: _files(files)
{
    cout << "RssReader()" << endl;
}

RssReader::~RssReader()
{
    cout << "~RssReader()" << endl;
}

void RssReader::loadFeedFiles()
{
    for(size_t idx = 0; idx != _files.size(); ++ idx)
    {
        cout << "has load" << idx + 1 << "rss files" << endl; 
        loadFeedFile(_files[idx]);
    }
}

void RssReader::loadFeedFile(const string & fileName)
{
    XMLDocument doc;
    doc.LoadFile(fileName.c_str());
    cout << "loadFile: " << fileName << endl;
    XMLError errorID = doc.ErrorID();
    if(errorID)
    {
        cout << "XMLDocument LoadField error" << endl;
        return;
    }
    else
    {
        parseRss(doc);
    }
}


void RssReader::makePages(vector<string> & pages)
{
    cout << "pages's size = " << _items.size() << endl;
    for(size_t idx = 0; idx != _items.size(); ++idx)
    {
        ostringstream oss;
        oss << "<doc>\n"
            << "  <docid>" <<(idx + 1) <<
            "</docid>\n"
            << "  <title>" << _items[idx]->_title
            << "</title>\n"
            << "  <link>"  << _items[idx]->_link
            << "</link>\n"
            << "  <content>" << _items[idx]->_content << "</contet>\n"
            <<"/<doc>\n";
        string page = oss.str();
        pages.push_back(page);
    }
}

void RssReader::parseRss(XMLDocument & doc)
{
    cout << "parsRss(XMLDocument & doc)" << endl;
    XMLElement * root = doc.FirstChildElement();
    XMLElement * channel = root->FirstChildElement("channel");
    XMLElement * item = channel->FirstChildElement("item");
    for(; item; item = item->NextSiblingElement())
    {
        shared_ptr<RssItem> rssItemPtr(new RssItem);
        const char * itemTitle = item->FirstChildElement("title")->GetText();
        const char * itemLink = item->FirstChildElement("link")->GetText();
        const char * itemDescription = item->FirstChildElement("description")->GetText();
        const char * iContent = nullptr;

        XMLElement * contentEncoded = item->FirstChildElement("content:encoded");
        if(contentEncoded)
        {
            iContent = contentEncoded->GetText();
        }
        else
        {
            iContent = itemDescription;
        }

        string szReg = "<.*?>";
        regex fmt(szReg);
        string content = regex_replace(string(iContent), fmt, string(""));

        rssItemPtr->_title = itemTitle ? itemTitle : string("");
        rssItemPtr->_link = itemLink ? itemLink : string("");
        rssItemPtr->_content = content;
        _items.push_back(rssItemPtr);
    }
}

#if 0

string RssReader::debug()
{}

void RssReader::dump(const string & fileName)
{
    
}
#endif



