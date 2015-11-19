/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator
{
private:
    stack<TreeNode*> s;
public:
    BSTIterator(TreeNode *root)
    {
        while (root!=nullptr)
        {
            s.push(root);
            root = root->left;
        }
    }
    bool hasNext()
    {
        return !s.empty();
    }
    int next()
    {
        if (!hasNext())
        {
            return INT_MIN;
        }
        TreeNode *node = s.top();
        int res = node->val;
        s.pop();
        if (node->right != nullptr)
        {
            node = node->right;
            s.push(node);
            while (node->left!=nullptr)
            {
                node = node->left;
                s.push(node);
            }
        }
        return res;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */