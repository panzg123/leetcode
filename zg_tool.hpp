//
// Created by zgpan on 2020/3/1.
//

#ifndef LEETCODE_ZG_TOOL_HPP
#define LEETCODE_ZG_TOOL_HPP

#include <string>
#include <vector>
#include <set>
#include <ostream>
#include <sstream>
using namespace std;

class ZgTool{
public:
    template<typename T>
    static string tostr(const T &t)
    {
        ostringstream sBuffer;
        sBuffer << t;
        return sBuffer.str();
    }

    template<typename T>
    static string tostr(const vector<T> &t)
    {
        string s;
        for(size_t i = 0; i < t.size(); i++)
        {
            s += tostr(t[i]);
            s += " ";
        }
        return s;
    }

    template<typename T>
    static string tostr(const set<T> &t)
    {
        string s;
        for(auto it = t.begin(); it != t.end(); ++it)
        {
            s += tostr(*it);
            s += " ";
        }
        return s;
    }


    /*
     * MyStrSplit 字符串分割函数
     */
    static vector<string> MyStrSplit(const string& sSource, const string& sPattern){
        vector<string> vRetData;
        if(sSource.empty())
            return vRetData;
        size_t iPos = sSource.find(sPattern);
        size_t iStart = 0;
        while(iPos != std::string::npos){
            vRetData.push_back(sSource.substr(iStart, iPos - iStart));
            iStart = iPos + sPattern.size();
            iPos = sSource.find(sPattern, iStart);
        }
        if(iStart < sSource.size()){
            vRetData.push_back(sSource.substr(iStart));
        }
        return vRetData;
    }
};

#endif //LEETCODE_ZG_TOOL_HPP
