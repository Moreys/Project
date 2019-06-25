/*************************************************************************
  @FileName:  ReadFile.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 23时45分15秒
 ************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <dirent.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define PATH "/root/project/searchEngline/offline/data/rss/"

class Test
{
public:
    Test(const string & path)
    : _files(path)
    {
        cout << _files << endl;
        tarverse(_files);
    }
    void tarverse(const string & dirName)
    {
        cout << dirName << endl;
        DIR * pDir = ::opendir(dirName.c_str());
        if(NULL == pDir)
        {
            cout << "打开目录错误" << endl;
            exit(EXIT_FAILURE);
        }
        ::chdir(dirName.c_str());
        struct dirent * pDirent;
        struct stat mystat;
        while(NULL != (pDirent = ::readdir(pDir)))
        {
            ::stat(pDirent->d_name, &mystat);
            if(S_ISDIR(mystat.st_mode))
            {
                if(0 == ::strncmp(pDirent->d_name, ".", 1) || 
                   0 == ::strncmp(pDirent->d_name, "..", 2))
                {
                    continue;
                }
                else
                {
                    tarverse(pDirent->d_name);
                }
            }
            else
            {
                string fileName;
                fileName.append(::getcwd(NULL, 0))
                    .append("/")
                    .append(pDirent->d_name);
                _vecFiles.push_back(fileName);
            }
        }
        ::chdir("..");
        ::closedir(pDir);
    }
    void debug()
    {
        for(auto & elem : _vecFiles)
        {
            cout << elem << endl;
        }
    }
private:
    vector<string> _vecFiles;
    string _files;
};
int main()
{
    Test t1(PATH);
    t1.debug();
    std::cout << "Hello world" << std::endl;
    return 0;
}

