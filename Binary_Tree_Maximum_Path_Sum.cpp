// LeetCode, Binary Tree Maximum Path Sum
// ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(logn)
class Solution
{
public:
    int maxPathSum(TreeNode *root)
    {
        max_sum = INT_MIN;
        dfs(root);
        return max_sum;
    }
private:
    int max_sum;
    int dfs(const TreeNode *root)
    {
        if (root == nullptr) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        int sum = root->val;
        if (l > 0) sum += l;
        if (r > 0) sum += r;
        max_sum = max(max_sum, sum);
        return max(r, l) > 0 ? max(r, l) + root->val : root->val;
    }
};