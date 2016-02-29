//Count Complete Tree Nodes，直接层次遍历，超时
int countNodes(TreeNode* root)
{
    queue<TreeNode*> q;
    int count = 0;
    if (root != nullptr)
        q.push(root);
    else
        return 0;
    while (!q.empty())
    {
        if (q.front()->left != nullptr)
            q.push(q.front()->left);
        if (q.front()->right != nullptr)
            q.push(q.front()->right);
        count++;
        q.pop();
    }
    return count;
}
//递归方法，参考：https://leetcode.com/discuss/73892/a-very-clear-recursive-solution-isnt-it
int countNodes_recursive(TreeNode* root)
{
    if (root == nullptr)
        return 0;
    int left_height = countNodes_helper(root->left);
    int right_height = countNodes_helper(root->right);
    if (left_height == right_height)
        return (1 << left_height) + countNodes_recursive(root->right);
    else
        return (1 << right_height) + countNodes_recursive(root->left);
}
//计算树的深度
int countNodes_helper(TreeNode* root)
{
    if (root == nullptr)
        return 0;
    else
        return 1 + countNodes_helper(root->left);
}