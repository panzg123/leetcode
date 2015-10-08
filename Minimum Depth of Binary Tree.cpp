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
	/*Minimum Depth of Binary Tree ตÝน้*/
   int minDepth(TreeNode* root)
	{
	    if (root == nullptr) return 0;
		return minDepth(root, 1);
	}
	int minDepth(TreeNode* root, int depth)
	{
		if (root == nullptr)
			return -1;
		int left_depth = minDepth(root->left,depth+1);
		int right_depth = minDepth(root->right,depth+1);
		if (left_depth != -1 && right_depth != -1)
			return min(left_depth, right_depth);
		else if (left_depth == -1 && right_depth != -1)
			return right_depth;
		else if (left_depth != -1 && right_depth == -1)
			return left_depth;
		else
			return depth;
	}
};