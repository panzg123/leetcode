/*前缀树 */
class TrieNode
{
public:
    int path;
    int end;
    unordered_map<int,TrieNode*> map;
    // Initialize your data structure here.
    TrieNode()
    {
        path = 0;
        end = 0;
    }
};

class Trie
{
public:
    Trie()
    {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word)
    {
        if (word == "")
            return;
        TrieNode *node = root;
        int index = 0;
        for (int i = 0; i < word.length(); i++)
        {
            index = word[i] - 'a';
            if (node->map.find(index) == node->map.end())
            {
                node->map[index] = new TrieNode();
            }
            node = node->map[index];
            node->path++;
        }
        node->end++;
    }

    // Returns if the word is in the trie.
    bool search(string word)
    {
        if (word == "")
            return false;
        TrieNode *node = root;
        int index = 0;
        for (int i = 0; i < word.length(); i++)
        {
            index = word[i] - 'a';
            if (node->map.find(index) == node->map.end())
            {
                return false;
            }
            node = node->map[index];
        }
        return node->end != 0;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix)
    {
        if (prefix == "")
            return false;
        TrieNode *node = root;
        int index = 0;
        for (int i = 0; i < prefix.length(); i++)
        {
            index = prefix[i] - 'a';
            if (node->map.find(index)==node->map.end())
            {
                return false;
            }
            node = node->map[index];
        }
        return node->path;
    }

private:
    TrieNode* root;
};
