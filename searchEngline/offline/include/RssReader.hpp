/*************************************************************************
  @FileName:  RssReader.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 17时30分54秒
 ************************************************************************/
                                                                         
#ifndef __RSSREADER_HPP__
#define __RSSREADER_HPP__

#include "tinyxml2.h"
#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;
using namespace tinyxml2;

struct RssItem
{
    string _title;
    string _link;
    string _pubData;
    string _content;
};

struct RssData
{
    string _version;
    string _title;
    string _link;
    string _description;
    string _language;
    vector<shared_ptr<RssItem>> _items;
};

class RssReader
{
public:
    RssReader(vector<string> &files); 
    ~RssReader();
    void loadFeedFiles();
    void loadFeedFile(const string & fileName);
    void initWithRssString(const string & rss);
    void makePages(vector<string> & pages);
private:
    void parseRss(XMLDocument & doc);
    string debug();
    void dump(const string & fileName);
private:
    vector<shared_ptr<RssItem>> _items;
    vector<string> & _files;
};

#endif

