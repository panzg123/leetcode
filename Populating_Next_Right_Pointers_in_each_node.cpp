/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
	/*�ݹ飬ʱ��O(n),�ռ䳣��*/
    void connect(TreeLinkNode *root) {
        if (root == nullptr) return;
		TreeLinkNode dump(-1);
		for (TreeLinkNode *pre=&dump,*cur=root;cur; cur=cur->next)
		{
			if (cur->left != nullptr)
			{
				pre->next = cur->left;
				pre = pre->next;
			}
			if (cur->right != nullptr)
			{
				pre->next = cur->right;
				pre = pre->next;
			}
		}
		connect(dump.next);
    }
};