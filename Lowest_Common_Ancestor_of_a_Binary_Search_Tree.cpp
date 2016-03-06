// Lowest Common Ancestor of a Binary Search Tree,https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// 直接递归
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if (p->val<root->val && q->val < root->val)
        return lowestCommonAncestor(root->left, p, q);
    if (p->val > root->val && q->val>root->val)
        return lowestCommonAncestor(root->right, p, q);
    return root;
}