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
	/*Binary Tree Right Side View 层次遍历*/
    vector<int> rightSideView(TreeNode* root)
    {
        queue<TreeNode*> q1,q2;
        if (root!=nullptr)
            q1.push(root);
        vector<int> result;
        while (!q1.empty())
        {
            result.push_back(q1.back()->val);
            while (!q1.empty())
            {
                TreeNode *top = q1.front();
                q1.pop();
                if (top->left)
                    q2.push(top->left);
                if (top->right)
                    q2.push(top->right);
            }
            swap(q1, q2);
        }
        return result;
    }
};