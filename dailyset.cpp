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
};


int main()
{
    Solution sol;
    cout << sol.canMeasureWater(3,5,4) << endl;
    return 0;
}