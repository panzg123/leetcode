//Binary Tree Paths,https://leetcode.com/problems/binary-tree-paths/
//求所有从根节点到叶子节点的路径，DFS问题
vector<string> binaryTreePaths(TreeNode* root)
{
    vector<string> ret;
    if (root == nullptr)
        return ret;
    binaryTreePaths_dfs(root,ret,"");
    return ret;
}
void binaryTreePaths_dfs(TreeNode* root,vector<string>& ret,string path)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        path += to_string(root->val);
        ret.push_back(path);
        return;
    }
    path += to_string(root->val);
    path += "->";
    if (root->left != nullptr)
        binaryTreePaths_dfs(root->left, ret, path);
    if (root->right != nullptr)
        binaryTreePaths_dfs(root->right, ret, path);
}