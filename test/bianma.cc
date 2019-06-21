/*************************************************************************
  @FileName:  bianma.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月21日 星期五 20时50分19秒
 ************************************************************************/


#include  <iostream>
#include <string.h>
#include <string>
#include <vector>
using namespace std ;
namespace morey
{

typedef string  Character;

class Test
{
public:
    vector<string> getOneChareacter( string  word)
    {
        auto cit = word.begin();
        vector<Character> ret;
#if 0
        while(cit < word.end())
        {
            Character tmp(1, *cit);
            ret.push_back(tmp);
            cit++;

        }
#endif

#if 1
        while(cit < word.end())
        {
            if(224 == (*cit & 224))
            {
                cout << "1" << endl;
                Character temp;
                temp.append(cit, cit + 3);
                ret.push_back(temp);
                cit = cit + 3;
            }
            else if(240 == (*cit & 240))
            {
                cout << "2" << endl;
                Character tmp;
                tmp.append(cit, cit + 4);
                ret.push_back(tmp);
                cit = cit + 4;
            }
            else
            {
                cout << "3" << endl;
                Character tmp(1, *cit);
                ret.push_back(tmp);
                cit++;
            }
        }
#endif
        return ret;
    }
};


}
using namespace morey;
int main()
{
    Test t1;
    t1.getOneChareacter("我是谁");
    vector<string> tmp = t1.getOneChareacter("中文处理");
    for(auto & elem : tmp)
    {
        cout << elem << endl;
    }
    return 0;
}
