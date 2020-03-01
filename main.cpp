//
// Created by zgpan on 2020/02/10.
//


#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <unordered_set>
using namespace std;

class Solution{

public:
    /*392. 判断子序列*/
    bool isSubsequence(string s, string t) {
        unordered_map<char,set<int> > mChStat;
        for(auto& ch : s)
        {
            set<int> setIdx;
            for(size_t idx = 0; idx < t.size(); ++idx)
            {
                if( ch == t[idx])
                {
                    setIdx.insert(static_cast<int &&>(idx));
                }
            }
            if(!setIdx.empty())
                mChStat[ch] = setIdx;
        }

        //依次判断是否满足条件
        int iLastPos = -1;
        for (auto& ch : s)
        {
            if(!mChStat.count(ch))  //如果不包含这个字符，则直接退出
                return false;
            auto& setPos = mChStat[ch];
            bool bMatch = false;
            for (int setPo : setPos) {
                //cout << "for 2, ch=" << ch << "\t*it=" << *it << endl;
                if(setPo > iLastPos)
                {
                    iLastPos = setPo;
                    bMatch = true;
                    break;
                }
            }
            if(!bMatch) return false; //没有找到合适的位置，则直接返回
        }
        return true;
    }

    /*双指针v2*/
    bool isSubsequenceV2(string s, string t) {
        auto iterS = s.begin();
        auto iterT = t.begin();
        while( iterS != s.end() && iterT != t.end())
        {
            if(*iterS == *iterT)
                ++iterS;
            ++iterT;
        }
        return iterS == s.end();
    }
};


int main()
{
    //cout <<"hello world" << endl;
    Solution sol;
    string s = "abc";
    string t = "ahbgdc";
    cout << sol.isSubsequenceV2( s, t) << endl;
    return 0;
}