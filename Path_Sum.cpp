/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
      if (root == nullptr) return false;
		if (root && root->left == nullptr && root->right == nullptr)
			return root->val == sum;
		bool flag_left = false, flag_right = false;
		if (root->left)
			flag_left = hasPathSum(root->left, sum - root->val);
		if (root->right)
			flag_right = hasPathSum(root->right, sum - root->val);
		return flag_left || flag_right;
    }
};