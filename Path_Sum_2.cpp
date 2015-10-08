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
	/*Path Sum 2 求所有路径的集合 递归*/
    vector<vector<int>> pathSum(TreeNode* root, int sum)
	{
		vector<int> vec;
		return pathSum_help(root, vec, sum);
	}
	vector<vector<int>> pathSum_help(TreeNode* root,vector<int> path_vec,int sum)
	{
		vector<vector<int>> res_vec;
		if (root == nullptr) return res_vec;
		if (root->left == nullptr && root->right == nullptr)
		{
			if (sum == root->val)
			{
				path_vec.push_back(sum);
				res_vec.push_back(path_vec);
			}
			return res_vec;
		}
		path_vec.push_back(root->val);
		auto left_res = pathSum_help(root->left, path_vec, sum - root->val);
		res_vec.insert(res_vec.begin(), left_res.begin(), left_res.end());
		auto right_res = pathSum_help(root->right, path_vec, sum - root->val);
		res_vec.insert(res_vec.begin(), right_res.begin(), right_res.end());

		return res_vec;
	}
};