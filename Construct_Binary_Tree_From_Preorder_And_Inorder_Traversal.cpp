/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    /*Construct Binary Tree from Preorder and Inorder Traversal
	??*/
   TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		return buildTree(begin(preorder), end(preorder), begin(inorder), end(inorder));
	}
	template<typename InputIterator>
	TreeNode* buildTree(InputIterator pre_first, InputIterator pre_last, InputIterator in_first, InputIterator in_last)
	{
		if (pre_first == pre_last) return nullptr;
		if (in_first == in_last) return nullptr;
		TreeNode * root = new TreeNode(*pre_first);;
		auto in_pos = find(in_first, in_last, *pre_first);
		auto length = distance(in_first, in_pos);

		root->left = buildTree(next(pre_first), next(pre_first, length + 1), in_first, next(in_first, length));
		root->right = buildTree(next(pre_first, length + 1), pre_last, next(in_pos), in_last);

		return root;
	}
};