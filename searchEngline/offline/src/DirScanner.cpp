/*************************************************************************
  @FileName:  DirScanner.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月24日 星期一 15时47分09秒
 ************************************************************************/

#include "Configuration.hpp"
#include "DirScanner.hpp"
#include "GlobalDefine.hpp"
#include "Mylog.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <dirent.h>
#include <iostream>


namespace morey
{

DirScanner::DirScanner(Configuration & conf)
: _conf(conf)
{
    _vecFiles.reserve(kFileNo);
}

void DirScanner::operator()()
{
    map<string, string>  & confMap = _conf.getConfigMap();
    string dirName = confMap[RSSPATH_KEY];
    tarverse(dirName);
}
vector<string>  & DirScanner::files()
{
    return _vecFiles;
}

void DirScanner::tarverse(const string & dirName)
{
#if 0 //获取当前目录下的文件没有问题，不能循环获取
    struct dirent * pDirInfo;
    DIR * pDir;
    pDir = opendir(dirName.c_str());
    if(NULL == pDir)
    {
        LogError("open dir fail");
        exit(EXIT_FAILURE);
    }
    string fileName;
    while(NULL != (pDirInfo = readdir(pDir)))
    {
        fileName = pDirInfo->d_name;
        if(fileName == "." || fileName == "..")
        {
            continue;
        }
        _vecFiles.push_back(dirName + fileName);
    }
#endif

#if 1  //循环获取文件有问题
    DIR * pDir = opendir(dirName.c_str());
    if(NULL == pDir)
    {
        LogError("open dir fail");
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
#endif
}

void DirScanner::debug()
{
    for(auto & elem : _vecFiles)
    {
        std::cout << elem << std::endl;
    }
}
}//end of namespace morey

