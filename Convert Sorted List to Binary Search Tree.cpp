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
	/*Convert Sorted Array to Binary Search Tree，递归*/
    TreeNode* sortedArrayToBST(vector<int>& nums)
	{
		int length = nums.size();
		if (length == 0) return nullptr;
		sortedArrayToBST_help(nums, 0, length - 1);
	}
	TreeNode* sortedArrayToBST_help(vector<int> &nums,int start,int end)
	{
		TreeNode *ret_node = new TreeNode(-1);
		if (start == end) //终止条件
		{
			ret_node->val = nums[start];
			return ret_node;
		}
		if (start > end) //合并两个元素出出现start>end
			return nullptr;
		int mid = (start + end) / 2;
		ret_node->val = nums[mid];
		TreeNode *left = sortedArrayToBST_help(nums, start, mid-1);
		TreeNode *right = sortedArrayToBST_help(nums, mid + 1, end);
		ret_node->left = left;
		ret_node->right = right;
		return ret_node;
	}
};