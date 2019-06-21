/*************************************************************************
  @FileName:  reanFile.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月21日 星期五 19时28分41秒
 ************************************************************************/
                                                                         
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

int main()
{
    struct dirent * pDirInfo;
    DIR * pDir;
    pDir = opendir("/root/project/oP/offline/data/cndict");
    if(NULL == pDir)
    {
        perror("open dir fail");
        return -1;
    }
    vector<string> File;
    string name;
    while((pDirInfo = readdir(pDir)) != NULL)
    {
        name = pDirInfo->d_name;
        if(name == "." || name == "..")
        {
            continue;
        }
        File.push_back(pDirInfo->d_name);
    }
    for(auto & elem : File)
    {
        std::cout << elem << std::endl;
    }
    closedir(pDir);
    return 0;
}

