//给定一颗二叉树，求此二叉树的最大距离，题目见《程序员代码面试指南》p169,时间复杂度O(N)
int maxDistance(TreeNode* root)
{
    auto ret = maxDistance_helper(root);
    return ret.first;
}
//一个后续遍历的过程
pair<int,int> maxDistance_helper(TreeNode* root)
{
    if(root == nullptr)
        return make_pair(0,0);
    auto left = maxDistance_helper(root->left);
    auto right = maxDistance_helper(root->right);
    pair<int, int> ret;//first成员记录最远距离，second成员记录距离root节点的最大距离
    ret.first = max(max(left.first, right.first),left.second+right.second+1);
    ret.second = max(left.second, right.second) + 1;
    return ret;
}