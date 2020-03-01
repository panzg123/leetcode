//
// Created by zgpan on 2020/3/1.
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


struct ListNode {
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
    /*
     * title:二维数组中的查找
     * 选取右上角或者左下角的点进行比较，每次剔除一行或者一列数据
     * 注意这里不能选取左上角或者右下角的点进行比较，那样不能排除数据，缩小范围
     */
    bool Find(int target, vector<vector<int> > array) {
        if(array.empty())
            return false;
        int iRowCnt = array.size();
        int iColCnt = array[0].size();
        int iRowIdx = 0 ;
        int iColIdx = iColCnt-1;

        while(iRowIdx < iRowCnt && iColIdx >= 0){
            if(array[iRowIdx][iColIdx] == target) {
                return true;
            }
            else if(array[iRowIdx][iColIdx] < target){
                ++iRowIdx;
            }
            else{
                --iColIdx;
            }
        }
        return false;
    }

    /*
     * title:替换空格，将字符串中的空格符替换为"%20"
     * 思路：不需要新分配空间，先计算空格的数量，从后往前拷贝
     */
    void replaceSpace(char *str,int length) {
        if(str == NULL || length <= 0 )
            return;
        //先计算空格的个数
        char* pTmp = str;
        int iCntSpace = 0;
        int iStrLen = 0;
        while(*pTmp != '\0'){
            ++iStrLen;
            if(*pTmp == ' ')
                ++iCntSpace;
            ++pTmp;
        }
        //给新的字符串分配空间
        int i = iStrLen;
        int j = iStrLen + 2*iCntSpace;
        if(j > length) // 空间不足，内存覆盖
            return;
        while(i>=0 &&  j>= i){
            if(*(str+i) == ' '){
                str[j] = '0';
                str[j-1] = '2';
                str[j-2] = '%';
                j -= 3;
            }
            else{
                str[j] = str[i];
                --j;
            }
            --i;
        }
    }

    /*
     * title：从尾到头打印链表
     * 思路：如果允许修改链表，则逆转链表；如果不允许修改，则栈存储或者递归
     */
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> vRetData;
        if(head == NULL)
            return vRetData;
        stack<int> stData;
        ListNode* pCur = head;
        while(pCur != NULL){
            stData.push(pCur->val);
            pCur = pCur->next;
        }
        while(!stData.empty()){
            vRetData.push_back(stData.top());
            stData.pop();
        }
        return vRetData;
    }

    /*
     * title:重建二叉树
     */
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.empty() || vin.empty() || pre.size() != vin.size())
            return NULL;
        TreeNode* pRoot = new TreeNode(pre[0]);
        if(pre.size() == 1)
            return pRoot;
        //下面从中序寻找节点
        auto iFindRet = std::find(vin.begin(), vin.end(), pRoot->val);
        if(iFindRet == vin.end()) return NULL;
        int iDistance = std::distance(vin.begin(), iFindRet);
        cout << "root:" << pRoot->val << ",dis=" << iDistance << endl;
        pRoot->left = reConstructBinaryTree(vector<int>(pre.begin() + 1, pre.begin() + 1 +iDistance),
                vector<int>(vin.begin(), vin.begin() + iDistance));
        pRoot->right = reConstructBinaryTree(vector<int>(pre.begin() + 1 + iDistance, pre.end()),
                vector<int>(vin.begin() + 1 + iDistance, vin.end()));
        return pRoot;
    }

    /*
     * title:旋转数组的最小数字
     */
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.empty())
            return 0;
        int iStart = 0;
        int iEnd = rotateArray.size() - 1;
        int iMid = 0;
        while(iStart < iEnd){
            if(rotateArray[iStart] < rotateArray[iEnd]){
                return rotateArray[iStart];
            }
            iMid = (iStart + iEnd) / 2;
            if(rotateArray[iMid] > rotateArray[iStart]){
                iStart = iMid +1;
            }else if(rotateArray[iMid] < rotateArray[iEnd]){
                iEnd = iMid;
            }else{
                ++iStart;
            }
        }
        return rotateArray[iStart];
    }

    /*
     * title: 矩形覆盖的方法数目
     */
    int rectCover(int number) {
        if(number==1) return 1;
        if(number==2) return 2;

        int f1 = 1, f2 = 2, f3 = 3;
        for (int i = 3; i <= number; ++i) {
            f3 = f1 + f2;
            f1 = f2;
            f2 = f3;
        }
        return f3;
    }
};


/*
 * title：两个栈实现一个队列
 */
class QueueMakeOf2Stack
{
public:
    void push(int node) {
        stack1.push(node);
    }
    int pop() {
        //先把stack1的数据都导入stack2
        if(stack2.empty()) {
            while (!stack1.empty()) {
                int node = stack1.top();
                stack2.push(node);
                stack1.pop();
            }
        }
        //把stack2顶部元素弹出
        int iRetData = stack2.top();
        stack2.pop();
        return iRetData;
    }
private:
    stack<int> stack1;
    stack<int> stack2;
};

int main()
{
    auto pre = {41,1,1,0,1};
    Solution sol;
    std::cout << sol.rectCover(5) << std::endl;
    return 0;
}