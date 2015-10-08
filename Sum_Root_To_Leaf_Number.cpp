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
	/*时间复杂度 O(n)，空间复杂度 O(logn)*/
    int sumNumbers(TreeNode* root)
	{
		sumNumbers_help(root, 0);
	}
	int sumNumbers_help(TreeNode *root, int sum)
	{
		if (root == nullptr) return 0;
		if (root->left == nullptr && root->right == nullptr)
			return 10 * sum + root->val;
		return sumNumbers_help(root->left, 10 * sum + root->val) 
			+ sumNumbers_help(root->right, 10 * sum + root->val);
	}
};