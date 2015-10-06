class Solution
{
public:
    /*inorderTraversal，栈 用标志位来记录是否访问过*/
    vector<int> inorderTraversal(TreeNode* root)
    {
        typedef struct node_flag
        {
            TreeNode *node;
            int flag = 0;  //标记位
            node_flag(TreeNode * val) :node(val) {}
        };
        stack<node_flag> stack_tree;
        vector<int> result;
        if (root == nullptr)
            return result;
        node_flag flag_root(root);
        stack_tree.push(flag_root);

        while (!stack_tree.empty())
            {
                node_flag  ptr_tree = stack_tree.top();
                if (ptr_tree.flag ==1)
                    result.push_back(ptr_tree.node->val);
                stack_tree.pop();

                if (ptr_tree.node->right != nullptr && ptr_tree.flag == 0)
                    {
                        node_flag flag_right(ptr_tree.node->right);
                        stack_tree.push(flag_right);
                    }

                //left_flag来保存标记
                int left_flag = ptr_tree.flag;
                if (ptr_tree.flag == 0)
                    {
                        ptr_tree.flag = 1;
                        stack_tree.push(ptr_tree);
                    }

                if (ptr_tree.node->left != nullptr && left_flag == 0)
                    {
                        node_flag flag_left(ptr_tree.node->left);
                        stack_tree.push(flag_left);
                    }

            }
        return result;
    }
    /*使用栈，时间复杂度 O(n)，空间复杂度 O(n)*/
    vector<int> inorderTraversal_v2(TreeNode *root)
    {
        vector<int> result;
        const TreeNode *p = root;
        stack<const TreeNode *> s;
        while (!s.empty() || p != nullptr)
            {
                if (p != nullptr)
                    {
                        s.push(p);
                        p = p->left;
                    }
                else
                    {
                        p = s.top();
                        s.pop();
                        result.push_back(p->val);
                        p = p->right;
                    }
            }
        return result;
    }
    // Morris 中序遍历，时间复杂度 O(n)，空间复杂度 O(1)
    vector<int> inorderTraversal_v3(TreeNode *root)
    {
        vector<int> result;
        TreeNode *cur, *prev;
        cur = root;
        while (cur != nullptr)
            {
                if (cur->left == nullptr)
                    {
                        result.push_back(cur->val);
                        prev = cur;
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
                                node->right = cur;
                                /* prev = cur; 不能有这句， cur 还没有被访问 */
                                cur = cur->left;
                            }
                        else     /* 已经线索化，则访问节点，并删除线索 */
                            {
                                result.push_back(cur->val);
                                node->right = nullptr;
                                prev = cur;
                                cur = cur->right;
                            }
                    }
            }
        return result;
    }
};