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
    int maxDepth(TreeNode* root) 
		{
			return maxDepth_helper(root, 0);
		}
		int maxDepth_helper(TreeNode* root, int depth)
		{
			if (root == nullptr)
				return depth;
			else
				return max(maxDepth_helper(root->left,depth+1), maxDepth_helper(root->right,depth+1));
		}
};