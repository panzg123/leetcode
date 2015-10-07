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
    /*flatten binary tree to linked list*/
	void flatten(TreeNode* root)
	{
	    if(root == nullptr) return;
		vector<TreeNode*> node_vec;
		flatten_preorder(root, node_vec);
		size_t length = node_vec.size();
		for (size_t i = 1; i < length; i++)
		{
			node_vec[i-1]->right = node_vec[i];
			node_vec[i - 1]->left = nullptr;
		}
		node_vec[length - 1]->right = nullptr;
		node_vec[length - 1]->left = nullptr;
	}
	void flatten_preorder(TreeNode* root, vector<TreeNode*> &res)
	{
		if (root == nullptr) return;
		res.push_back(root);
		flatten_preorder(root->left,res);
		flatten_preorder(root->right,res);
	}
};