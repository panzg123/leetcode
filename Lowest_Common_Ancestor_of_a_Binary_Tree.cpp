//Lowest Common Ancestor of a Binary Tree,https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
//二叉树中的LCA问题，递归解决
TreeNode* lowestCommonAncestor_2(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if (!root || root == p || root == q)
        return root;
    TreeNode* left = lowestCommonAncestor_2(root->left, p, q);
    TreeNode* right = lowestCommonAncestor_2(root->right, p, q);
    //情况1：p&q节点都在root右子树
    if (left == nullptr)
        return right;
    else
    {
        //情况2：p和q都在root的左子树
        if (right == nullptr)
            return left;
        //情况3：p和q分别在root的左右子树
        else
            return root;
    }
}