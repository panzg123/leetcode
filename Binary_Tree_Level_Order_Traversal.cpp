class Solution
{
public:
    /*Binary Tree Level Order Traversal，用level来记录深度*/
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        typedef struct level_tree
        {
            TreeNode *node;
            int level;
            level_tree(TreeNode *node1, int level1) :node(node1), level(level1) {}
        } level_tree;
        vector<vector<int>> result;
                         queue<level_tree> q;
                         if (root == nullptr) return result;
                         level_tree tree_node(root, 0);
                         q.push(tree_node);
                         int level_flag = 0;
                         vector<int> ivec;
                         while (!q.empty())
            {
                level_tree temp_node = q.front();
                q.pop();
                if (temp_node.level != level_flag)
                    {
                        result.push_back(ivec);
                        vector<int> tep;
                        swap(tep, ivec);
                        ivec.clear();
                        level_flag += 1;
                    }
                ivec.push_back(temp_node.node->val);
                if (temp_node.node->left != nullptr)
                    {
                        level_tree left_node(temp_node.node->left, temp_node.level + 1);
                        q.push(left_node);
                    }
                if (temp_node.node->right != nullptr)
                    {
                        level_tree left_node(temp_node.node->right, temp_node.level + 1);
                        q.push(left_node);
                    }
            }
        if (!ivec.empty())
            result.push_back(ivec);
        //下面一行用于level order 2题
        //reverse(result.begin(), result.end());
        return result;
    }
    // 递归版，时间复杂度 O(n)，空间复杂度 O(n)
    vector<vector<int> > levelOrder_v2(TreeNode *root)
    {
        vector<vector<int>> result;
        traverse(root, 1, result);
        return result;
    }
    void traverse(TreeNode *root, size_t level, vector<vector<int>> &result)
    {
        if (!root) return;
        if (level > result.size())
            result.push_back(vector<int>());
        result[level-1].push_back(root->val);
        traverse(root->left, level+1, result);
        traverse(root->right, level+1, result);
    }
};