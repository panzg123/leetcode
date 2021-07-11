//
// Created by zgpan on 2020/6/25.
// leetcode 每日一题
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <stack>
#include <queue>
#include <climits>
#include "zg_tool.hpp"
using namespace std;

struct ListNode{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {
    }
};

//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    //最长回文字串，https://leetcode-cn.com/problems/longest-palindrome/
    int longestPalindrome(string s) {
        map<char,int> mapCharCnt;
        for(auto item : s){
            ++mapCharCnt[item];
        }
        int maxLen = 0;
        bool bExist = false; //奇数是否存在
        for(auto item : mapCharCnt){
            if(item.second%2 == 0)
                maxLen += item.second;
            else {
                bExist = true;
                if(item.second > 1){
                    maxLen += item.second - 1;
                }
            }
        }
        if(bExist) maxLen += 1;
        return maxLen;
    }

    //水壶问题，https://leetcode-cn.com/problems/water-and-jug-problem/
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a%b);
    }
    bool canMeasureWater(int x, int y, int z) {
        if (x + y < z) return false;
        if (x == 0 || y == 0) return z == 0 || x + y == z;
        return z % gcd(x, y) == 0;
    }

    //二叉树的直径，https://leetcode-cn.com/problems/diameter-of-binary-tree/
    int diameterOfBinaryTree(TreeNode* root) {

    }

    // 山脉数组的峰顶索引 https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/
    int peakIndexInMountainArray(vector<int>& arr) {
        int low = 0, high = arr.size() - 1;
        while(low < high) {
            auto mid = (low + high) / 2;
            if(arr[mid] > arr[low]) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return low;
    }

    // 1239. 串联字符串的最大长度
    int maxLength(vector<string>& arr) {
        vector<string> ret = arr;
        for (int i = 0; i < arr.size()-1; ++i) {
            string  str = arr[i];
            for (int j = i+1; j < arr.size(); ++j) {
                str.append(arr[j]);
            }
            ret.push_back(str);
        }
        //挨个计算
        int max_len = 0;
        for (auto str : ret) {
            map<char,int> cnt;
            bool repeat = false;
            for(auto c : str) {
                if (cnt[c] == 1) {
                    repeat = true;
                    break;
                }
                cnt[c] = 1;
            }
            if (!repeat){
                max_len = max(max_len, int(str.length()));
            }
        }
        return max_len;
    }

    // 剑指 Offer 38. 字符串的排列
    vector<string> permutation(string s) {
        vector<string> ret;
        std::sort(s.begin(), s.end());
        ret.push_back(s);
        while (next_permutation(s.begin(), s.end()))
        {
            ret.push_back(s);
        }
        return ret;
    }
    // v2 使用交换法
    void permutation_dfs(string s, int pos, set<string>& ret) {
        // 第一个元素与其它位置元素交换
        if(pos == s.size() - 1) {
            ret.insert(s);
            return
        }
        permutation_dfs(s, pos + 1, ret);
        for (size_t i = pos + 1; i < s.size(); i++)
        {
            //交换
            if(s[i] != s[pos]) {
                swap(s[i], s[pos]);
                permutation_dfs(s, pos + 1, ret);
                swap(s[i], s[pos]);
            }
        }
        return;
    }


    // 49. 直线上最多的点数
    bool NodeLine(vector<int> a, vector<int> b, vector<int> c) {
        if ( (b[1]-a[1])*(c[0]-a[0]) == (b[0]-a[0])*(c[1]-a[1])) {
            return true;
        }
        return false;
    }
    int maxPoints(vector<vector<int>>& points) {
        int max_num = 0;
        for (size_t i = 0 ; i < points.size(); ++i){
            for (size_t j = i+1; j < points.size(); ++j) {
                bool vertical = false;
                if (points[i][0] == points[j][0]) {
                    vertical = true;
                }
                int cnt = 0;
                for (size_t k = 0; k < points.size(); k++)
                {
                    if (vertical && points[k][0] == points[j][0]) {
                        ++cnt;
                    } 
                    if (!vertical && (NodeLine(points[i], points[j], points[k])) {
                        ++cnt;
                    }
                }
                max_num = max(max_num, cnt);
            }
        }
        return max_num;
    }

    // 645. 错误的集合
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int> data;
        if(nums.empty()) return  data;
        data.resize(nums.size());
        fill(data.begin(), data.end(), 0);

        vector<int> ret;
        for(auto item : nums){
            ++data[item-1];
            // 找到重复的号码
            if (data[item-1] == 2) {
                ret.push_back(item);
            }
        }

        // 找出不存在的号码
        for(size_t i = 0; i < data.size(); ++i) {
            if(data[i] == 0) {
                ret.push_back(i+1);
            }
        }
        return ret;
    }

    // 451. 根据字符出现频率排序
    struct CharTimes{
        char c;
        int cnt;
    };
    bool CharTimesCmp(CharTimes left, CharTimes right) {
        return left.cnt > right.cnt;
    }
    string frequencySort(string s) {
        map<char,int> cnt;
        for (size_t i = 0; i < s.size(); i++)
        {
            ++cnt[s[i]];
        }
        //排序
        vector<CharTimes> data;
        for (auto item : cnt)
        {
            CharTimes ct;
            ct.c = item.first;
            ct.cnt = item.second;
            data.push_back(ct);
        }
        sort(data.begin(), data.end(), CharTimesCmp);
        // 拼接
        ostringstream oss;
        for(auto item : data) {
            for (size_t i = 0; i < item.cnt; i++)
            {
                oss << item.c;
            }
        }
        return oss.str();
    }

    // 274. H 指数
    int hIndex(vector<int>& citations) {
        vector<int> cnt(citations.size(), 0);
        for(size_t i = 1; i <= citations.size(); ++i) {
            for(auto item : citations) {
                if (item >= i) {
                    ++cnt[i-1];
                }
            }
        }
        int max_value = 1;
        for(size_t i = 0; i < cnt.size(); ++i){
            if(cnt[i] >= i + 1) {
                max_value = max(max_value, cnt[i]);
            }
        }
        return max_value;
    }

    // 274. H 指数 先排序，在计算
    int hIndexV2(vector<int>& citations) {
        if(citations.empy()) return 0;
        sort(citations.begin, citations.end());
        int len = citations.size();
        int i = 0;
        while( i < len && citations[i] < len - i) {
            ++i;
        }
        return len - i;
    }
};


int main()
{
    Solution sol;
    //vector<int> data = {24,69,100,99,79,78,67,36,26,19};
    //cout << sol.peakIndexInMountainArray(data) << endl;
    //vector<string> data = {"cha","r","act","ers"};
    string data = "abc";
    cout << data << endl;
    sol.permutation(data);
    return 0;
}