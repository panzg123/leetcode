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
    /*Unique Binary Search Trees II,递归*/
	vector<TreeNode*> generateTrees(int n)
	{
		if (n == 0) return generate_bst_tree(1, 0);
		return generate_bst_tree(1, n);
	}
	vector<TreeNode*> generate_bst_tree(int start, int end)
	{
		vector<TreeNode*> subTree;
		if (start > end)
		{
			subTree.push_back(nullptr);
			return subTree;
		}
		for (int k = start; k <= end; k++)
		{
			vector<TreeNode*> leftSubs = generate_bst_tree(start, k - 1);
			vector<TreeNode*> rightSubs = generate_bst_tree(k + 1, end);
			for (auto i : leftSubs)
			{
				for (auto j : rightSubs)
				{
					TreeNode * node = new TreeNode(k);
					node->left = i;
					node->right = j;
					subTree.push_back(node);
				}
			}
		}
		return subTree;
	}
};