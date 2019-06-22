/*************************************************************************
  @FileName:  test.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月20日 星期四 08时35分48秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

using Character = string;
class Test
{
public:

#if 0
    int minDistance(string word1, string word2) 
    {
        vector<Character> queryChara = getOneChareacter();
        vector<Character> indexChara = getOneChareacter(rhs);
        int n1 = word1.size(), n2 = word2.size();
        int dp[n1 + 1][n2 + 1];
        for (int i = 0; i <= n1; ++i) dp[i][0] = i;
        for (int i = 0; i <= n2; ++i) dp[0][i] = i;
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                }
            }
        }
        return dp[n1][n2];
    }
#endif

#if 1
    int minDistance(string word1, string word2) 
    {
        vector<Character> queryChara = getOneChareacter(word1);
        vector<Character> indexChara = getOneChareacter(word2);
        int n1 = queryChara.size(), n2 = indexChara.size();
        int dp[n1 + 1][n2 + 1];
        for (int i = 0; i <= n1; ++i) dp[i][0] = i;
        for (int i = 0; i <= n2; ++i) dp[0][i] = i;
        for (int i = 1; i <= n1; ++i)
        {
            for (int j = 1; j <= n2; ++j) 
            {
                if (queryChara[i - 1] == indexChara[j - 1]) 
                {
                    dp[i][j] = dp[i - 1][j - 1];
                } 
                else 
                {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                }
            }
        }
        return dp[n1][n2];
    }


    int cnDistance(string word1, string word2)
    {
        vector<Character> queryChara = getOneChareacter(word1);
        vector<Character> indexChara = getOneChareacter(word2);
        int n1 = queryChara.size(), n2 = indexChara.size();
        int dp[n1 + 1][n2 + 1];
        for(int i = 0; i <= n1; ++i)
        {
            dp[i][0] = i;
        }
        for(int i = 0; i <= n2; ++i)
        {
            dp[0][i] = i;
        }
        int temp;
        for(int i = 1; i <= n1; ++i)
        {
            for(int j = 1; j <= n2; ++j)
            {
                if(word1.at(i - 1) == word2.at(j -1))
                {
                    temp = 0;
                }
                else
                {
                    temp = 1;
                }
            }
        }
    return dp[n1][n2];
    }

#endif
    int distance( string & rhs,string & lhs )
    {
        vector<Character> queryChara = getOneChareacter(lhs);
        vector<Character> indexChara = getOneChareacter(rhs);
        int len1, len2;
        len1 = queryChara.size();
        len2 = indexChara.size();
        int edit[len1 + 1][len2 + 1];
        int i, j;
        for(i = 0; i < len1; ++i)
        {
            for(j = 0; j < len2; ++j)
            {
                edit[i][j] = 0;
            }
        }
        for(i=0;i<len1;++i)
        {
            edit[i][0]=i;
        }
        for(j=0;j<=len2;++j)
        {
            edit[0][j]=j;
        }
        for(i = 1; i < len1; ++i)
        {
            for(j = 1; j <= len2; ++j)
            {
                int cost = ((queryChara[i - 1] == indexChara[j - 1]) ? 0 : 1);
                int deletion = edit[i - 1][j] + 1;
                int insertion = edit[i][j - 1] + 1;
                int substitution = edit[i - 1][j - 1] + cost;
                edit[i][j] = min(deletion, min(insertion,substitution));
            }
        }
        return edit[len1][len2];
    }


    vector<Character>getOneChareacter(const string & word)
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
                Character temp;
                temp.append(cit, cit + 3);
                ret.push_back(temp);
                cit = cit + 3;

            }
            else if(240 == (*cit & 240))
            {
                Character tmp;
                tmp.append(cit, cit + 4);
                ret.push_back(tmp);
                cit = cit + 4;
            }
            else
            {
                Character tmp(1, *cit);
                ret.push_back(tmp);
                cit++;
            }
        }
#endif
#if 0
        for(auto & elem: ret)
        {
            cout << elem << endl;
        }
#endif
        return ret;
    }
    
};

int main()
{
    string s1 = "我也是你大爷";
    string s2 = "hello";
    cout << s1.size() << endl;
    cout << s2.size() << endl;
    Test t1;
    cout << t1.minDistance(s1, s2) << endl;
    cout << "-------------------" << endl;
    cout << t1.distance(s1, s2) << endl;
    std::cout << "Hello world" << std::endl;
    return 0;
}

