class Solution
{
public:
    /*Binary Tree Zigzag Level Order Traversal，递归*/
    vector<vector<int>> zigzagLevelOrder(TreeNode* root)
    {
        vector<vector<int>> result;
        zigzag_traverse(root, 0, result);
        return result;
    }
    void zigzag_traverse(TreeNode *root, size_t level, vector<vector<int>> &result)
    {
        if (!root) return;
        if (level+1 > result.size())
            result.push_back(vector<int>());
        if (level % 2 == 0) result[level].push_back(root->val);
        else result[level].insert(result[level].begin(), root->val);

        zigzag_traverse(root->left, level + 1, result);
        zigzag_traverse(root->right, level + 1, result);
    }
    /*迭代*/
    vector<vector<int> > zigzagLevelOrder_v2(TreeNode *root)
    {
        vector<vector<int> > result;
        if (nullptr == root) return result;
        queue<TreeNode*> q;
        bool left_to_right = true; //left to right，反转标志位
        vector<int> level; // one level's elements
        q.push(root);
        q.push(nullptr); // level separator
        while (!q.empty())
            {
                TreeNode *cur = q.front();
                q.pop();
                if (cur)
                    {
                        level.push_back(cur->val);
                        if (cur->left) q.push(cur->left);
                        if (cur->right) q.push(cur->right);
                    }
                else
                    {
                        if (left_to_right)
                            {
                                result.push_back(level);
                            }
                        else
                            {
                                reverse(level.begin(), level.end());
                                result.push_back(level);
                            }
                        level.clear();
                        left_to_right = !left_to_right;
                        if (q.size() > 0) q.push(nullptr);
                    }
            }
        return result;
    }
};