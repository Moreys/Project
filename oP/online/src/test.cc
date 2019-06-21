/*************************************************************************
  @FileName:  test.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月21日 星期五 16时43分55秒
 ************************************************************************/

#include "Segmentation.hpp"
#include <iostream>


#include<iostream>
#include<string>
#include<vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace morey;

int main()
{
    string str="结巴分词库的下载和应用";
    Segmentation wordSeg;
    vector<string> results=wordSeg(str);
    cout<<"分词结果如下:"<<endl;
    for(auto it=results.begin();it!=results.end();++it)
    {
        cout<<*it<<" ";
    }
    return 0;
}
