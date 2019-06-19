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
#include <functional>
#include <algorithm>

using namespace std;
class Test
{
public:
    Test(string str)
        : _str(str)
    {}
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

    void findWorld()
    {
        set<int> setTmp;
        set<int> setTmp2;
        for(int idx = 0; idx != (int)_str.length(); ++idx)
        {
            if(idx == 0)
            {
                map<string, set<int>>::iterator it = _mapIdx.find(to_string(_str[idx]));
                setTmp = it->second;
                _setIdx = setTmp;
                break;
            }
            //else//第二次和后面的都要求交集。
           // {
            //    map<string, set<int>>::iterator it1 = _mapIdx.find(to_string(_str[idx]));
             //   set_intersection(setTmp.begin(), setTmp.end(),
              //                   it1->second.begin(), it1->second.end(), setTmp2);    
               // setTmp.clear();
                //setTmp = setTmp2;
                //setTmp2.clear();
            //}
        }
    }
    void pritfSet()
    {
        for(auto & elem : _setIdx)
        {
            cout << elem << endl;
        }
    }
private:
    string _str;
    map<string, set< int>> _mapIdx;
    set<int> _setIdx;
    vector<std::pair<string, int>> _vecIdx;
};


int main()
{
    while(1)
    {
        string str; 
        if(!(cin >> str) || str == "q")break; 
        Test t1(str);
        t1.pushvec(); 
        t1.setIndex();
        t1.findWorld();
        cout << "-------------->";
        t1.pritfSet();
    }
    std::cout << "Hello world" << std::endl;
    return 0;
}

