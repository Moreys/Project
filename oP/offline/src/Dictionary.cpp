/*************************************************************************
  @FileName:  Dictionary.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月17日 星期一 10时28分25秒
 ************************************************************************/

#include "Dictionary.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

namespace morey
{
void Dictionary::read(const string & filename)
{
    ifstream ifs(filename);
    if(!ifs)
    {
        cout << ">>>ifstream open file" << filename << "error" << endl;
        return ;
    }
    string line;
    while(ifs >> line)
    {
        map<string,int>::iterator it = _count.find(line);
        if(it == _count.end())
        {
            _count.insert(map<string, int>::value_type(line,1));    
        }
        else 
        {
            ++_count[line];
        }
    }
    ifs.close();
}

void Dictionary::store(const string & filename)
{
    ofstream ofs(filename);
    if(!ofs)
    {
        cout << ">>>ifstream open file" << filename << "error" << endl;
        return ;
    }
    for(const auto & elem : _count)
    {
        ofs << elem.first << "   " <<  elem.second << endl;
    }
    ofs.close();
}

void Dictionary::getline()
{
    map<string,int>::iterator it = _count.find("int");
        if(it == _count.end())
        {
            cout << it->first << it->second << endl;
        }
}

void Dictionary::dispose(
                         const string & filenameIfs,
                         const string & filenameOfs)
{
    cout << filenameIfs << endl;
    cout << filenameOfs << endl;
    ifstream ifs(filenameIfs);
    ofstream ofs(filenameOfs);
    if(!ifs)
    {
        cout << "ifstream open file " << filenameIfs << "error" << endl;
        return;
    }
    if(!ofs)
    {
        cout << "ofstream open file " << filenameOfs << "error" << endl;
        return;
    }
    char oneWorld;
    string ling;
    while(std::getline(ifs, ling))//没有进循环，下午在看看
    {
                
        for(int idx = 0; idx != (int)ling.size(); ++idx)
        {
           if(ispunct(ling[idx]))
           {
                oneWorld = ' ';
                ling[idx] = oneWorld;
           }
           ling[idx] = tolower(ling[idx]);
        }
        ofs << ling;
        ofs << "\n";
    }
    ifs.close();
    ofs.close();
}
}//end of namespace morey


