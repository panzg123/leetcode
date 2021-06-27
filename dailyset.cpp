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