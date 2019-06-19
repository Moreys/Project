/*************************************************************************
  @FileName:  tt.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月17日 星期一 22时11分38秒
 ************************************************************************/
                                                                         
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class Test
{
public:
void setIndex()
{
    int flag = 15;
    string str;
    stringstream stream;
    set<int> setInd;
    for(int idx = 'a'; idx != 'z' + 1; ++idx)
    {
        stream << (char)idx;
        str = stream.str();
        stream.str("");
        for(auto & elem : _vecIdx)
        {
            for(int i = 0; i != flag; ++i)
            {
                if(elem.first[i] == idx)
                {
                    cout <<  &elem - &_vecIdx[0] << " ";
                    setInd.insert(&elem - &_vecIdx[0]);
                    _mapIdx[str] = setInd;
                    break;
                }
            }
        }
        cout << endl;
        setInd.clear();
    }
}
void pushvec()
{
    _vecIdx.push_back(std::make_pair("ipone",111));
    _vecIdx.push_back(std::make_pair("iphone",1911));
    _vecIdx.push_back(std::make_pair("nike",1));
    _vecIdx.push_back(std::make_pair("kindle",11));
    _vecIdx.push_back(std::make_pair("loop",11));
    _vecIdx.push_back(std::make_pair("appl",11));
    _vecIdx.push_back(std::make_pair("soopy",11));
    _vecIdx.push_back(std::make_pair("ndle",11));
    _vecIdx.push_back(std::make_pair("kile",11));
}
void pritT()
{
    for(auto & elem : _mapIdx)
    {
        cout << elem.first << " ";
        for(auto & lem : elem.second)
            cout << lem << " ";
        cout << endl;
    }   
}
private:
    map<string, set< int>> _mapIdx;
    set<int> _setIdx;
    vector<std::pair<string, int>> _vecIdx;
};


int main()
{
    Test t1;
    t1.pushvec();
    t1.setIndex();
    cout << "-------------------" << endl;
    t1.pritT();
    std::cout << "Hello world" << std::endl;
    return 0;
}

