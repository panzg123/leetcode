//计算一个完全二叉树的节点数目
int nodeNum(TreeNode* root)
{
    if (root == nullptr)
        return 0;
    return nodeNum_helper(root,1,mostLeftLevel(root,1));
}
int nodeNum_helper(TreeNode* root,int cur_level,int high)
{
    if (cur_level == high)
        return 1;
    if (mostLeftLevel(root->right, cur_level + 1) == high) //左子树满二叉树
        return (1 << (high - cur_level)) + nodeNum_helper(root->right, cur_level + 1, high);
    else //右子树满二叉树
        return (1 << (high - cur_level - 1)) + nodeNum_helper(root->left, cur_level + 1, high);
}
//计算当前root节点所在的level
int mostLeftLevel(TreeNode* root, int level)
{
    while (root != nullptr)
    {
        level++;
        root = root->left;
    }
    return level - 1;
}