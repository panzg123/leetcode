class Solution
{
public:
    /*Binary Tree Preorder Traversal , 递归版本*/
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> result;
        if (root == nullptr) return result;
        result.push_back(root->val);
        vector<int> left = preorderTraversal(root->left);
        result.insert(result.end(), left.begin(), left.end());
        vector<int> right = preorderTraversal(root->right);
        result.insert(result.end(), right.begin(), right.end());
        return result;
    }
    /*非递归，用栈*/
    vector<int> preorderTraversal_v2(TreeNode *root)
    {
        stack<TreeNode*> stack_tree;
        vector<int> result;
        if (root == nullptr)
            return result;
        stack_tree.push(root);
        while (!stack_tree.empty())
            {
                TreeNode * ptr_tree = stack_tree.top();
                result.push_back(ptr_tree->val);
                stack_tree.pop();
                if (ptr_tree->right != nullptr)
                    stack_tree.push(ptr_tree->right);
                if (ptr_tree->left != nullptr)
                    stack_tree.push(ptr_tree->left);
            }
        return result;
    }
    // LeetCode, Binary Tree Preorder Traversal
    // Morris 先序遍历，时间复杂度 O(n)，空间复杂度 O(1)
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> result;
        TreeNode *cur, *prev;
        cur = root;
        while (cur != nullptr)
            {
                if (cur->left == nullptr)
                    {
                        result.push_back(cur->val);
                        prev = cur; /* cur 刚刚被访问过 */
                        cur = cur->right;
                    }
                else
                    {
                        /* 查找前驱 */
                        TreeNode *node = cur->left;
                        while (node->right != nullptr && node->right != cur)
                            node = node->right;
                        if (node->right == nullptr)   /* 还没线索化，则建立线索 */
                            {
                                result.push_back(cur->val); /* 仅这一行的位置与中序不同 */
                                node->right = cur;
                                prev = cur; /* cur 刚刚被访问过 */
                                cur = cur->left;
                            }
                        else     /* 已经线索化，则删除线索 */
                            {
                                node->right = nullptr;
                                /* prev = cur; 不能有这句， cur 已经被访问 */
                                cur = cur->right;
                            }
                    }
            }
        return result;
    }
};