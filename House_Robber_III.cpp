//https://leetcode.com/problems/house-robber-iii/
unordered_map<TreeNode*, int> cache;
int rob(TreeNode* root)
{
    if (root == NULL) return 0;
    unordered_map<TreeNode*, int>::iterator it = cache.find(root);
    if (it != cache.end()) return it->second;
    int sum1 = root->val;//选择root节点
    int sum2 = 0; //不选择root节点
    if (root->left != NULL)
    {
        sum1 += rob(root->left->left) + rob(root->left->right);
        sum2 += rob(root->left);
    }
    if (root->right != NULL)
    {
        sum1 += rob(root->right->left) + rob(root->right->right);
        sum2 += rob(root->right);
    }
    int res = sum1 > sum2 ? sum1 : sum2;
    cache[root] = res;
    return res;
}