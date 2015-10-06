class Solution
{
public:
    /*用栈，用flag来记录是否被访问*/
    vector<int> postorderTraversal(TreeNode* root)
    {
        typedef struct node_flag
        {
            TreeNode *node;
            int flag = 0;
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
                if (ptr_tree.flag == 1)
                    result.push_back(ptr_tree.node->val);
                stack_tree.pop();

                int left_flag = ptr_tree.flag;
                if (ptr_tree.flag == 0)
                    {
                        ptr_tree.flag = 1;
                        stack_tree.push(ptr_tree);
                    }

                if (ptr_tree.node->right != nullptr && left_flag == 0)
                    {
                        node_flag flag_right(ptr_tree.node->right);
                        stack_tree.push(flag_right);
                    }


                if (ptr_tree.node->left != nullptr && left_flag == 0)
                    {
                        node_flag flag_left(ptr_tree.node->left);
                        stack_tree.push(flag_left);
                    }

            }
        return result;
    }
    // Morris 后序遍历，时间复杂度 O(n)，空间复杂度 O(1)
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        TreeNode dummy(-1);
        TreeNode *cur, *prev = nullptr;
        std::function < void(const TreeNode*)> visit =
            [&result](const TreeNode *node)
        {
            result.push_back(node->val);
        };
        dummy.left = root;
        cur = &dummy;
        while (cur != nullptr)
            {
                if (cur->left == nullptr)
                    {
                        prev = cur; /* 必须要有 */
                        cur = cur->right;
                    }
                else
                    {
                        TreeNode *node = cur->left;
                        while (node->right != nullptr && node->right != cur)
                            node = node->right;
                        if (node->right == nullptr)   /* 还没线索化，则建立线索 */
                            {
                                node->right = cur;
                                prev = cur; /* 必须要有 */
                                cur = cur->left;
                            }
                        else     /* 已经线索化，则访问节点，并删除线索 */
                            {
                                visit_reverse(cur->left, prev, visit);
                                prev->right = nullptr;
                                prev = cur; /* 必须要有 */
                                cur = cur->right;
                            }
                    }
            }
        return result;
    }
private:
	// 逆转路径
    static void reverse(TreeNode *from, TreeNode *to)
    {
        TreeNode *x = from, *y = from->right, *z;
        if (from == to) return;
        while (x != to)
            {
                z = y->right;
                y->right = x;
                x = y;
                y = z;
            }
    }
	// 访问逆转后的路径上的所有结点
    static void visit_reverse(TreeNode* from, TreeNode *to,
                              std::function< void(const TreeNode*) >& visit)
    {
        TreeNode *p = to;
        reverse(from, to);
        while (true)
            {
                visit(p);
                if (p == from)
                    break;
                p = p->right;
            }
        reverse(to, from);
    }
};