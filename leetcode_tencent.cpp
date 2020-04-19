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
#include <climits>
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

    //最接近的三数之和
    int threeSumClosest(vector<int>& nums, int target) {
        int iMinSumDis = INT_MAX;
        int iRetTraget = 0;
        if(nums.size() < 3) return 0;
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; ++i) {
            int j = i + 1;
            int k = nums.size() - 1;
            while( j < k){
                int sum = nums[i] + nums[j] + nums[k];
                if(abs(sum - target) < iMinSumDis)
                {
                    iMinSumDis = abs(sum - target);
                    iRetTraget = sum;
                }
                if(sum > target) --k;
                else if(sum < target) ++j;
                else
                    return target;
            }
        }
        return  iRetTraget;
    }

    //删除排序数组中的重复项
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        int iNewIdx = 0;
        int iOldIdx = 1;
        while(iOldIdx < nums.size()){
            if(nums[iOldIdx] == nums[iNewIdx])
                ++iOldIdx;
            else
                nums[++iNewIdx] = nums[iOldIdx++];
        }
        return iNewIdx + 1;
    }


    //反转字符串
    void reverseString(vector<char>& s) {
        int i = 0;
        while( i  < (s.size() / 2) ){
            swap(s[i], s[s.size() - 1 - i]);
            ++i;
        }
    }

    //反转字符串中的单词 III
    string reverseWords(string s) {
        int iBegin = 0;
        int iEnd = 0;
        //find the whitespace
        while (iEnd < s.size())
        {
            while (s[iEnd] != ' ' && iEnd < s.size())
            {
                ++iEnd;
            }
            //cout << "iBegin=" << iBegin << ",iEnd=" << iEnd << endl;
            //交换s[iBegin, iEnd-1]
            for (size_t i = iBegin; i < iBegin + (iEnd - iBegin) / 2; i++)
            {
                swap(s[i], s[iEnd -1 -i+iBegin]);
            }
            iBegin = iEnd + 1;
            ++iEnd; //跳过空格
        }
        return s;
    }

    //存在重复元素
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> mCnt;
        for(auto item : nums)
        {
            if(mCnt.count(item))
                return true;
            else
                mCnt[item] = 1;
        }
        return false;
    }

    //合并两个有序数组
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int idx1 = m-1;
        int idx2 = n-1;
        int newIdx = m + n -1;
        while (idx1 >= 0 && idx2 >= 0)
        {
            if(nums1[idx1] > nums2[idx2])
            {
                nums1[newIdx--] = nums1[idx1--];
            }
            else
            {
                nums1[newIdx--] = nums2[idx2--];
            }
        }
        while (idx1 >= 0)
        {
            nums1[newIdx--] = nums1[idx1--];
        }

        while (idx2 >= 0)
        {
            nums1[newIdx--] = nums2[idx2--];
        }
    }

    //有效的括号
    bool isValid(string s) {
        if(s.empty()) return true;
        stack<char> stData;
        for(auto item : s)
        {
            if(item == '(' || item == '{' || item == '[')
            {
                stData.push(item);
            }
            else if(item == ')')
            {
                if (!stData.empty() && stData.top() == '(')
                    stData.pop();
                else
                    return false;
            }
            else if(!stData.empty() && item == '}')
            {
                if (stData.top() == '{')
                    stData.pop();
                else
                    return false;
            }
            else if(!stData.empty() && item == ']')
            {
                if (stData.top() == '[')
                    stData.pop();
                else
                    return false;
            }
            else
            {
                return false;
            }
        }
        return stData.empty();
    }

    //盛最多水的容器
    int maxArea(vector<int>& height) {
        int iLow = 0;
        int iHigh = height.size() - 1;
        int iMaxArea = INT_MIN;
        while(iLow < iHigh)
        {
            iMaxArea = max(iMaxArea, (iHigh - iLow)*(min(height[iLow], height[iHigh])));
            height[iLow] < height[iHigh] ? ++iLow : --iHigh;
        }
        return iMaxArea;
    }

    //字符串相乘
    string StrAddHelper(const string& str1, const string& str2)
    {
        string sRetStr;
        int iJinwei = 0;
        int idxStr1 = str1.size() - 1;
        int idxStr2 = str2.size() - 1;
        while (idxStr1 >= 0 && idxStr2 >= 0)
        {
            int iAddVal = str1[idxStr1] - '0' + str2[idxStr2] - '0' + iJinwei;
            iJinwei = iAddVal/10;
            sRetStr.push_back(iAddVal%10 + '0');
            --idxStr1;
            --idxStr2;
        }
        //补齐剩余的数
        while(idxStr1 >= 0)
        {
            int iAddVal = str1[idxStr1] - '0' + iJinwei;
            iJinwei = iAddVal/10;
            sRetStr.push_back(iAddVal%10 + '0');
            --idxStr1;
        }

        while (idxStr2 >= 0)
        {
            int iAddVal = str2[idxStr2] - '0' + iJinwei;
            iJinwei = iAddVal/10;
            sRetStr.push_back(iAddVal%10 + '0');
            --idxStr2;
        }

        if(iJinwei) sRetStr.push_back(iJinwei + '0');
        
        //反转字符串
        std::reverse(sRetStr.begin(), sRetStr.end());
        return sRetStr;
    }
    void TrimZero(string& str)
    {
        int idx = 0;
        while(idx < str.size() && str[idx] == '0')
        {
            ++idx;
        }
        if(idx == str.size())
            str = "0";
        else
        {
            str = str.substr(idx);
        }
    }

    //朴素方法，测试case都能通过，但是超时
    string multiply(string num1, string num2) {       
        string sRetStr = "0"; 
        //先处理下0字符
        TrimZero(num1);
        TrimZero(num2);
        if(num1 == "0" | num2 == "0") return sRetStr;

        int iJinwei = 0;
        for(int i = num2.size()-1; i >=0; --i)
        {
            iJinwei = 0;
            for(int j = num1.size()-1; j >=0; --j)
            {
                int iMulRet = (num1[j] - '0') * (num2[i] - '0') + iJinwei;
                iJinwei = iMulRet/10;
                string sVal = std::to_string(iMulRet%10);
                //插入N个0
                if(j != (num1.size() -1) || i != (num2.size() -1))
                    sVal.append(string(num1.size() + num2.size() -2 -i -j,'0'));
                //cout << "i=" << i << ",j=" << j << "sVal=" << sVal << ",imulRet=" << iMulRet << ",iJinwei=" << iJinwei << ",sRet=" << sRetStr << endl;
                sRetStr = StrAddHelper(sVal, sRetStr);
                //cout << sRetStr << endl;
            }

            if(iJinwei)
            {
                string strTmp;
                strTmp.push_back(iJinwei + '0');
                strTmp.append(string( num1.size() +  (num2.size() - i -1), '0'));
                sRetStr = StrAddHelper(sRetStr, strTmp);
            }
        }
        return sRetStr;
    }

    //优化版 pass
    string multiplyV2(string num1, string num2) 
    {
        string sRetStr(num1.size() + num2.size(), '0');
        for(int i = num2.size()-1; i >=0; --i)
        {
            for(int j = num1.size()-1; j >=0; --j)
            {
                int iMulRet = (num1[j] - '0') * (num2[i] - '0') + (sRetStr[i+j+1]- '0');
                sRetStr[i+j+1] = iMulRet%10 + '0';
                sRetStr[i+j] += iMulRet/10;
            }
        }

        //去除首部的0
        for (size_t i = 0; i < sRetStr.size(); i++)
        {
            if(sRetStr[i] != '0')
                return sRetStr.substr(i);
        }
        return "0";
    }

    //除自身以外数组的乘积-左右乘积
    // O(N)空间复杂度
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> vRetData(nums.size(), 1);
        if(nums.empty() || nums.size() == 1)
            return vRetData;
        vector<int> vLeft(nums.size(),1); //第i个数左边的乘积
        vector<int> vRight(nums.size(),1);//第i个数右边的乘积
        for(size_t i = 1; i < nums.size(); ++i)
        {
            vLeft[i] = vLeft[i-1] * nums[i-1];
        }
        for(int i = nums.size() - 2;  i >= 0;--i)
        {
            vRight[i] = vRight[i+1] * nums[i+1];
        }
        //左右相乘
        for(int i = 0; i < nums.size(); ++i)
        {
            vRetData[i] = vLeft[i] * vRight[i];
        }
        return vRetData;
    }
    //常数空间复杂度--实际上就是利用vRetData的空间，不再额外分配
    vector<int> productExceptSelfV2(vector<int>& nums) {
        vector<int> vRetData(nums.size(), 1);
        if(nums.empty() || nums.size() == 1)
            return vRetData;
        for(size_t i = 1; i < nums.size(); ++i){
            vRetData[i] = vRetData[i-1] * nums[i-1];
        }

        int iRightVal = 1; //用来记录从右往左的乘积
        //从右往左遍历
        for (int j = nums.size()-1; j >= 0; --j) {
            vRetData[j] = vRetData[j]*iRightVal;
            iRightVal *= nums[j];
        }
        return vRetData;
    }

    //逆转链表--递归
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr)
            return head;
        if(head->next == nullptr)
            return head;
        //先逆转后部分
        reverseListHelper(head);
        return head;
    }
    ListNode* reverseListHelper(ListNode* &head)
    {
        if(head->next == nullptr)
            return head;
        ListNode* headNode = head->next;
        ListNode* tailNode = reverseListHelper(headNode);
        tailNode->next = head;
        head->next = nullptr;
        head = headNode;
        return tailNode->next;
    }

    //逆转链表--迭代
    ListNode* reverseListV2(ListNode* head) {
        if(head == nullptr || head->next == nullptr)
            return head;
        ListNode* preNode = head;
        head = head->next;
        preNode->next = nullptr;
        while (head != nullptr){
            ListNode* nextNode  = head->next;
            head->next = preNode;
            preNode = head;
            head = nextNode;
        }
        return preNode;
    }

    //链表两数相加
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int iJinWei = 0;
        ListNode *headNode = new ListNode(-1);
        ListNode *preNode = headNode;
        while(l1 != nullptr && l2 != nullptr){
            int iVal = (l1->val + l2->val + iJinWei) % 10;
            iJinWei = (l1->val + l2->val + iJinWei) / 10;
            ListNode* curNode = new ListNode(iVal);
            preNode->next = curNode;
            preNode = curNode;

            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1 != nullptr){
            int iVal = (l1->val  + iJinWei) % 10;
            iJinWei = (l1->val + iJinWei) / 10;
            ListNode* curNode = new ListNode(iVal);
            preNode->next = curNode;
            preNode = curNode;
            l1 = l1->next;
        }

        while (l2 != nullptr){
            int iVal = (l2->val  + iJinWei) % 10;
            iJinWei = (l2->val + iJinWei) / 10;
            ListNode* curNode = new ListNode(iVal);
            preNode->next = curNode;
            preNode = curNode;
            l2 = l2->next;
        }

        //如果还有进位，则新建
        if(iJinWei != 0){
            ListNode* curNode = new ListNode(iJinWei);
            preNode->next = curNode;
            preNode = curNode;
        }
        return headNode->next;
    }

    //合并两个有序链表
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* TmpHead = new ListNode(-1);
        ListNode* preNode = TmpHead;
        while (l1 != nullptr && l2 != nullptr){
            if(l1->val < l2->val){
                preNode->next = l1;
                preNode = preNode->next;
                l1 = l1->next;
            }else{
                preNode->next = l2;
                preNode = preNode->next;
                l2 = l2->next;
            }
        }
        while (l1 != nullptr){
            preNode->next = l1;
            preNode = preNode->next;
            l1 = l1->next;
        }
        while (l2 != nullptr){
            preNode->next = l2;
            preNode = preNode->next;
            l2 = l2->next;
        }
        return TmpHead->next;
    }

    ListNode* findMinNode(vector<ListNode*>& lists){
        int iMinVal = INT_MAX;
        int iNodeIdx = -1;
        for(auto it = lists.begin(); it != lists.end(); ++it){
            if(it.operator*() != nullptr && it.operator*()->val < iMinVal){
                iNodeIdx = distance(lists.begin(), it);
                iMinVal = it.operator*()->val;
            }
        }
        //如果存在最小数
        if(iNodeIdx != -1){
            ListNode* retNode = lists[iNodeIdx];
            lists[iNodeIdx] = retNode->next;
            return retNode;
        }
        return nullptr;
    }
    //合并K个排序链表
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* tmpNode = new ListNode(-1);
        ListNode* preNode = tmpNode;
        ListNode* minNode = findMinNode(lists);
        while (minNode != nullptr){
            preNode->next = minNode;
            preNode = preNode->next;
            minNode = findMinNode(lists);
        }
        return tmpNode->next;
    }

    void PrintList(ListNode* node){
        while(node != nullptr)
        {
            cout << node->val << endl;
            node = node->next;
        }
    }

    //旋转链表
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr || k == 0) return head;
        //先计算size
        int iNodeCnt = 0;
        ListNode* node = head;
        ListNode* preNode = new ListNode(-1);
        preNode->next = node;
        while (node != nullptr){
            ++iNodeCnt;
            preNode = node;
            node = node->next;
        }
        k = k%iNodeCnt;
        //先把链表连起来
        preNode->next = head;
        //PrintList(head);
        //找到要断开的位置，即第iNodeCnt-k处
        node = head;
        int iTmpCnt = iNodeCnt - k; //第iNodeCnt-k处置空
        while(iTmpCnt-- > 1){
            node = node->next;
        }
        ListNode* retNode = node->next;
        node->next = nullptr;
        return retNode;
    }

    //判断链表中是否有环
    bool hasCycle(ListNode *head) {
        if(head == nullptr || head->next == nullptr) return false;
        ListNode* slowNode = head;
        ListNode* fastNode = head;
        while(slowNode != nullptr && fastNode != nullptr){
            slowNode = slowNode->next;
            fastNode = fastNode->next == nullptr ? nullptr :fastNode->next->next;
            if(slowNode == fastNode) return true;
        }
        return false;
    }

    //环形链表 II -- 找出环形节点入口
    ListNode *detectCycle(ListNode *head) {
        if(head == nullptr || head->next == nullptr) return nullptr;
        ListNode* slowNode = head;
        ListNode* slowNode2 = head;
        ListNode* fastNode = head;
        while(slowNode != nullptr && fastNode != nullptr){
            slowNode = slowNode->next;
            fastNode = fastNode->next == nullptr ? nullptr :fastNode->next->next;
            if(slowNode == fastNode)
            {
                while (slowNode2 != slowNode){
                    slowNode = slowNode->next;
                    slowNode2 = slowNode2->next;
                }
                return slowNode;
            }
        }
        return nullptr;
    }


    //相交链表--找到两个单链表相交的起始节点
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr || headB == nullptr)
            return nullptr;
        int iListLenA = 0;
        int iListLenB = 0;
        ListNode* nodeA = headA;
        ListNode* nodeB = headB;
        while (nodeA != nullptr){
            ++iListLenA;
            nodeA = nodeA->next;
        }
        while (nodeB != nullptr){
            ++iListLenB;
            nodeB = nodeB->next;
        }

        //长链表先走N步
        int iStepCnt = abs(iListLenB - iListLenA);
        nodeB  = headB;
        nodeA  = headA;
        if(iListLenA < iListLenB){
            while (iStepCnt--){
                nodeB = nodeB->next;
            }
        }else{
            while (iStepCnt--){
                nodeA = nodeA->next;
            }
        }

        //下面循环比较
        while(nodeA != nullptr && nodeB != nullptr){
            if(nodeA == nodeB)
                return nodeA;
            nodeA = nodeA->next;
            nodeB = nodeB->next;
        }
        return nullptr;
    }

    //删除链表中的节点--删除指定节点node
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        ListNode* tmpNode = node->next;
        node->next = node->next->next;
        delete tmpNode;
    }

};

int main()
{
    Solution sol;
    ListNode node1(4);
    ListNode node2(1);
    ListNode node3(8);
    ListNode node4(4);
    ListNode node5(5);
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;

    ListNode node6(5);
    ListNode node7(0);
    node6.next = &node7;
    node7.next = &node2;

//    ListNode node6(4);
//    node4.next =&node5;
//    node5.next =&node6;
//
//    ListNode node7(1);
//    ListNode node8(2);
//    node7.next = &node8;


    auto node = sol.getIntersectionNode(&node1, &node6);
    sol.PrintList(node);

    //cout << ZgTool::tostr(nums1) << endl;
}