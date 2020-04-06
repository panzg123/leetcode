//
// Created by zgpan on 2020/4/5.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
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
    //寻找两个有序数组的中位数 - 复杂度O(M+N)
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int i = 0, j = 0;
        bool needTwo  = false;
        int idxFirst = 0;
        if( (nums1.size() + nums2.size()) % 2) {
            needTwo = false;
            idxFirst = (nums1.size() + nums2.size()) / 2 + 1;
        } else{
            needTwo = true;
            idxFirst = (nums1.size() + nums2.size()) / 2;
        }

        int iCnt = 0;
        int iTotalVal = 0;
        while(i < nums1.size() || j < nums2.size()){
            ++iCnt;
            int iVal = 0;
            if(i < nums1.size() && j < nums2.size()) {
                if (nums1[i] < nums2[j]) {
                    iVal = nums1[i++];
                } else {
                    iVal = nums2[j++];
                }
            }else if(i >= nums1.size()){
                iVal = nums2[j++];
            }else if( j >= nums2.size()){
                iVal = nums1[i++];
            }

            if(!needTwo && iCnt == idxFirst)
                return iVal;
            else if(needTwo && iCnt == idxFirst + 1)
                return ((iTotalVal + iVal) / 2.0);
            else if(needTwo && iCnt == idxFirst)
                iTotalVal = iVal;
        }
        return 0;
    }

    /*找两个有序数组的中位数 - 时间复杂度O(log(m + n)) */
    //https://zhuanlan.zhihu.com/p/67542731
    double findMedianSortedArraysV2(vector<int>& nums1, vector<int>& nums2) {
        const int n1 = nums1.size();
        const int n2 = nums2.size();
        if(n1>n2) return findMedianSortedArrays(nums2, nums1);
        const int k = (n1 + n2 + 1)/2;
        int left = 0;
        int right = n1;
        while(left < right){
            const int m1 = left + (right - left)/2;
            const int m2 = k - m1;
            if(nums1[m1]<nums2[m2-1])
                left = m1 + 1;
            else
                right = m1;
        }
        const int m1 = left;
        const int m2 = k - left;
        const int c1 = max(m1 <= 0 ? INT_MIN:nums1[m1-1],
                           m2 <= 0 ? INT_MIN:nums2[m2-1]);
        if((n1 + n2)%2 == 1)
            return c1;
        const int c2 = min(m1 >= n1 ? INT_MAX: nums1[m1],
                           m2 >= n2 ? INT_MAX : nums2[m2]);
        return (c1 + c2) * 0.5;
    }

    //最长回文子串-动态规划问题
    string longestPalindrome(string s) {
        if(s.empty()) return "";
        vector<vector<int>> data(s.size(), vector<int>(s.size(), 1));
        int iMaxLen = 1;
        int iLow = 0, iHigh = 0;
        for (int i = s.size() - 2; i >= 0 ; --i) {
            //初始化一波
            if(s[i+1] == s[i])
            {
                data[i][i+1] = 2;
                if(iMaxLen < 2)
                {
                    iLow = i;
                    iHigh = i+1;
                    iMaxLen = 2;
                }
            }
            for (int j = i+2; j < s.size(); ++j) {
                if(s[j] == s[i] && data[i+1][j-1] >= (j-i-1) )
                {
                    data[i][j] = max(data[i+1][j-1] + 2, data[i][j-1]);
                }
                else
                    data[i][j] = data[i][j-1];
                if(data[i][j] > iMaxLen)
                {
                    iLow = i;
                    iHigh = j;
                    iMaxLen = data[i][j];
                }

            }
        }
        return s.substr(iLow, iHigh-iLow + 1);
    }

    //字符串转换整型
    int myAtoi(string str) {
        if(str.empty()) return 0;
        //先找到第一个非空字符
        int idx = 0;
        while( idx < str.size() && str[idx] == ' ' ){
            ++idx;
        }
        if(idx >= str.size()) return 0; //无效
        //第一个字符非法
        if( !( (str[idx] <= '9' && str[idx] >= '0') || str[idx] == '+' || str[idx] == '-' )){
            return 0;
        }

        bool bNeg = false;
        if(str[idx] == '-') {
            bNeg = true;
            ++idx;
        }else if(str[idx] == '+'){
            ++idx;
        }
        long lRet = 0;
        long lMaxInt = INT_MAX;
        while(idx < str.size()){
            if(str[idx] >= '0' && str[idx] <= '9'){
                lRet = lRet*10 + str[idx] - '0';
                ++idx;
                if(lRet >= (lMaxInt+1)) break;
            }else{
                break;
            }
        }
        if(!bNeg && lRet > INT_MAX) return INT_MAX;
        if(bNeg && lRet > (lMaxInt + 1)) return INT_MIN;
        return -1*lRet;
    }

    //最长公共前缀
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        int iMax = 0;
        bool bTerminate = false;
        do{
            char c;
            if(strs.front().size() > iMax)
                c = strs.front()[iMax];
            else
                break;
            for (int i = 1; i < strs.size(); ++i) {
                if(strs[i].size() <= iMax || strs[i][iMax] != c)
                {
                    bTerminate = true;
                    break;
                }
            }
            if(bTerminate) break;
            ++iMax;
        }while(true);
        if(iMax == 0) return "";
        return strs.front().substr(0,iMax);
    }

    //三数之和--左右夹逼
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> vRet;
        std::sort(nums.begin(), nums.end());
        if(nums.size() < 3) return vRet;
        for (int i = 0; i < nums.size() - 2;++i) {
            //这里要跳过重复的数
            if( i && nums[i] == nums[i-1]) continue;
            int j = i+1;
            int k = nums.size() - 1;
            while(j < k){
                int iTotal = nums[i] + nums[j] + nums[k];
                if(iTotal > 0)
                    --k;
                else if(iTotal < 0)
                    ++j;
                else
                {
                    vector<int> vItem = {nums[i], nums[j], nums[k]};
                    vRet.push_back(vItem);
                    --k;
                    ++j;
                    while( j < k && nums[j] == nums[j+1]) ++j; //跳过重复的解
                }
            }
        }
        return vRet;
    }
};

int main()
{
    Solution sol;
    cout << sol.myAtoi("   -42") << endl;
}