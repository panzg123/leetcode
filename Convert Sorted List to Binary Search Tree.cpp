/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    /*Convert Sorted List to Binary Search Tree
	自底向上,时间复杂度 O(n)，空间复杂度 O(logn)
	也可以自顶向下，时间复杂度为O(n^2)*/
	TreeNode* sortedListToBST(ListNode* head)
	{
		int length = 0;
		ListNode *temp = head;
		while (temp)
		{
			length++;
			temp = temp->next;
		}
		return sortedListToBST_help(head, 0, length - 1);
	}
	TreeNode* sortedListToBST_help(ListNode* &list, int start,int end)
	{
		if (start > end)
			return nullptr;
		int mid = (start + end) / 2;
		TreeNode *left = sortedListToBST_help(list, start, mid - 1);
		TreeNode *root = new TreeNode(-1);
		root->val = list->val;
		root->left = left;
		list = list->next;
		TreeNode *right = sortedListToBST_help(list, mid + 1, end);
		root->right = right;
		return root;
	}
};