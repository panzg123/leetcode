//Serialize and Deserialize Binary Tree
//二叉树的序列化与反序列化，递归，先序遍历序列化，另外也可以采用层次遍历序列化
class Codec
{
public:
    //分割字符串
    vector<std::string> split(std::string str, std::string pattern)
    {
        std::string::size_type pos;
        std::vector<std::string> result;
        str += pattern;//扩展字符串以方便操作
        int size = str.size();
        for (int i = 0; i < size; i++)
        {
            pos = str.find(pattern, i);
            if (pos < size)
            {
                std::string s = str.substr(i, pos - i);
                result.push_back(s);
                i = pos + pattern.size() - 1;
            }
        }
        return result;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        if (root == nullptr)
            return "#!";
        string ret = to_string(root->val) + "!";
        ret += serialize(root->left);
        ret += serialize(root->right);
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
        vector<string> split_ret = split(data, "!");
        split_ret.pop_back();
        queue<string> q;
        for (int i = 0; i < split_ret.size(); i++)
        {
            q.push(split_ret[i]);
        }
        return reconOrder(q);
    }
    TreeNode* reconOrder(queue<string> &q)
    {
        string value = q.front();
        q.pop();
        if (value == "#")
            return nullptr;
        TreeNode *root = new TreeNode(stoi(value));
        root->left = reconOrder(q);
        root->right = reconOrder(q);
        return root;
    }
};