//Kth Smallest Element in a BST,https://leetcode.com/problems/kth-smallest-element-in-a-bst/
//直接递归，时间复杂度O(N)，空间复杂度O(N)
int kthSmallest(TreeNode* root, int k)
{
    vector<int> result;
    kthSmallest_helper(root, result, k);
    if (result.size() == k)
        return result.back();
    else
        return 0;
}
void kthSmallest_helper(TreeNode *root, vector<int>& result,const int k)
{
    if (root == nullptr)
        return;
    //中序遍历的思路
    kthSmallest_helper(root->left, result, k);
    if (result.size() == k)
        return;
    else
        result.push_back(root->val);
    kthSmallest_helper(root->right, result, k);
}
//不用递归，用栈，时间复杂度O(N)，空间复杂度O(N)
int kthSmallest(TreeNode* root, int k)
{
    TreeNode* current = NULL;
    stack<TreeNode*> s;
    current = root;
    int count = 1;
    while (1)
    {
        while (current)
        {
            s.push(current);
            current = current->left;
        }
        if (count == k)
        {
            TreeNode* node = s.top();
            return node->val;
        }
        if (count != k)
        {
            TreeNode* node = s.top();
            s.pop();
            current = node->right;
            count++;
        }
    }
}