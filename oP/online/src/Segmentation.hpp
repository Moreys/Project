/*************************************************************************
  @FileName:  Segmentation.hpp
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月21日 星期五 16时19分40秒
 ************************************************************************/

#ifndef __SEGMENTATION_HPP__
#define __SEGMENTATION_HPP__
#include "../include/cppjieba/Jieba.hpp"

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::string;
using std::endl;
using std::vector;

namespace morey
{
const char* const DICT_PATH = "../libs/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../libs/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../libs/dict/user.dict.utf8";
const char* const IDF_PATH = "../libs/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../libs/dict/stop_words.utf8";
    class Segmentation
    {
    public:
        Segmentation()
            : _jieba(DICT_PATH,
                     HMM_PATH,
                     USER_DICT_PATH,
                     IDF_PATH,
                     STOP_WORD_PATH) {}

        vector<string> operator()(const string str)
        {
            vector<string> words;
            _jieba.CutAll(str, words);
            return words;
        }
    private:
        cppjieba::Jieba _jieba;
    };
}//end of namespace morey

#endif

