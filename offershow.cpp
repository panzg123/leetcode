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

    /*
     * title:二进制中1的个数
     */
    int  NumberOf1(int n) {
        int iCnt = 0;
        while(n){
            ++iCnt;
            n = n & (n-1);
        }
        return iCnt;
    }

    /*
     * title:翻转链表
     */
    ListNode* ReverseList(ListNode* pHead) {
        if(pHead == NULL || pHead->next == NULL)
            return pHead;
        ListNode* pPre = NULL;
        ListNode* pCur = pHead;
        ListNode* pNext = pHead->next;
        while(pCur){
            pNext = pCur->next;
            pCur->next = pPre;
            pPre = pCur;
            pCur = pNext;
        }
        return pPre;
    }

    /*
     * title：合并两个排序的链表
     */
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2){
        if(pHead1 == NULL)
            return pHead2;
        if(pHead2 == NULL)
            return pHead1;
        ListNode* pPre = new ListNode(0);
        ListNode* pHead = pPre;
        while(pHead1 != NULL && pHead2 != NULL){
            if(pHead1->val <= pHead2->val){
                pPre->next = pHead1;
                pPre = pPre->next;
                pHead1 = pHead1->next;
            }else{
                pPre->next = pHead2;
                pPre = pPre->next;
                pHead2 = pHead2->next;
            }
        }
        if(pHead1){
            while(pHead1){
                pPre->next = pHead1;
                pPre = pPre->next;
                pHead1 = pHead1->next;
            }
        }
        if(pHead2){
            while(pHead2){
                pPre->next = pHead2;
                pPre = pPre->next;
                pHead2 = pHead2->next;
            }
        }
        return pHead->next;
    }

    /*
     *title:树的子结构
     */
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2){
        bool bFind = false;
        if(pRoot1 != NULL && pRoot2 != NULL){
            if(pRoot1->val == pRoot2->val)
                bFind = DoesTreeContain(pRoot1, pRoot2);
            if(!bFind)
                bFind = HasSubtree(pRoot1->left, pRoot2);
            if(!bFind)
                bFind = HasSubtree(pRoot1->right, pRoot2);
        }
        return bFind;
    }
    bool DoesTreeContain(TreeNode* pRoot1, TreeNode* pRoot2){
        if(pRoot2 == NULL) return true;
        if(pRoot1 == NULL) return false;
        if(pRoot1->val != pRoot2->val)
            return false;
        return DoesTreeContain(pRoot1->left, pRoot2->left) &&
                DoesTreeContain(pRoot1->right, pRoot2->right);
    }

    /*
     * title: 树的镜像
     */
    void TreeMirror(TreeNode *pRoot) {

        /*
        if(pRoot == NULL) return;
        TreeNode* pTmp = pRoot->right;
        pRoot->right = pRoot->left;
        pRoot->left = pTmp;
        TreeMirror(pRoot->left);
        TreeMirror(pRoot->right);
         */

        //非递归的写法
        if(pRoot == NULL) return;
        queue<TreeNode*> qNode;
        qNode.push(pRoot);
        while(!qNode.empty()){
            TreeNode* pRootTmp = qNode.front();
            TreeNode* pTmp = pRootTmp->right;
            pRootTmp->right = pRootTmp->left;
            pRootTmp->left = pTmp;
            //判断子节点
            if(pRootTmp->left) qNode.push(pRootTmp->left);
            if(pRootTmp->right) qNode.push(pRootTmp->right);
            qNode.pop();
        }
    }

    /*
     * title: 栈的压入和弹出序列
     */
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        if(pushV.empty() || popV.empty() || pushV.size() != popV.size())
            return false;
        stack<int> stackTmp;
        stackTmp.push(pushV.front());
        auto popIt = popV.begin();
        auto pushIt = pushV.begin() + 1;
        while(popIt != popV.end()) {
            //如果顶部元素不是对应pop的元素，则一直压入
            while (stackTmp.top() != *popIt && pushIt != pushV.end()) {
                stackTmp.push(*pushIt++);
            }
            if(stackTmp.top() != *popIt) return false;
            stackTmp.pop();
            ++popIt;
        }
        return stackTmp.empty();
    }

    /*
     * title：从上往下打印二叉树
     */
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        queue<TreeNode*> qNode;
        vector<int> vNode;
        if(root == NULL) return vNode;
        qNode.push(root);
        while(!qNode.empty()){
            TreeNode* pRoot = qNode.front();
            vNode.push_back(pRoot->val);
            if(pRoot->left != NULL) qNode.push(pRoot->left);
            if(pRoot->right != NULL) qNode.push(pRoot->right);
            qNode.pop();
        }
        return vNode;
    }


    /*
     * title：判断是否二叉搜索树的后续遍历序列
     */
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.empty()) return false;
        if(sequence.size() == 1 ) return true;
        int iRootVal = sequence.back();
        //找到第一个比iRootVal大的元素
        bool bFind = false;
        int index = 0;
        for (int i = 0; i < sequence.size()-1; ++i) {
            if(sequence[i] > iRootVal){
                bFind = true;
                index = i;
                break;
            }
        }
        if(!bFind) return true;
        for (int j = index+1; j < sequence.size() - 1; ++j) {
            if(sequence[j] < iRootVal)
                return false;
        }
        bool bLeft = true, bRight = true;
        if(index != 0)
            bLeft = VerifySquenceOfBST(vector<int>(sequence.begin(), sequence.begin() + index));
        if(index != sequence.size() - 2)
            bRight = VerifySquenceOfBST(vector<int>(sequence.begin() + index, sequence.begin() + sequence.size() - 1));
        //再判断子序列
        return  bLeft && bRight;
    }

    /*
     * title: 二叉树中和为某一值得路径
     */
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        vector<int> vCurPath;
        vector<vector<int> > vPath;
        int iCurVal = 0;
        if(root==nullptr) return vPath;
        FindPathHelper(root, expectNumber, iCurVal, vPath, vCurPath);
        return vPath;
    }
    void FindPathHelper(TreeNode* root,int expectNumber, int iCurVal, vector<vector<int>>& vPath, vector<int>  curPath){
        curPath.push_back(root->val);
        iCurVal += root->val;
        if(root->left == nullptr && root->right == nullptr){
            if(iCurVal == expectNumber)
                vPath.push_back(curPath);
            return;
        }
        if(root->left != nullptr)
            FindPathHelper(root->left, expectNumber, iCurVal, vPath, curPath);
        if(root->right != nullptr)
            FindPathHelper(root->right, expectNumber, iCurVal, vPath, curPath);
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
    auto push = {5,4,3,2,1};
    auto pop = {4,3,5,1,2};
    Solution sol;
    std::cout << sol.VerifySquenceOfBST(push) << std::endl;
    return 0;
}