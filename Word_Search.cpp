// LeetCode, Word Search
// 深搜，递归
// 时间复杂度 O(n^2*m^2)，空间复杂度 O(n^2)
class Solution
{
public:
    bool exist(vector<vector<char> > &board, string word)
    {
        const int m = board.size();
        const int n = board[0].size();
        vector<vector<bool> > visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (dfs(board, word, 0, i, j, visited))
                    return true;
        return false;
    }
private:
    static bool dfs(const vector<vector<char> > &board, const string &word,
                    int index, int x, int y, vector<vector<bool> > &visited)
    {
        if (index == word.size())
            return true; // 收敛条件
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size())
            return false; // 越界，终止条件
        if (visited[x][y]) return false; // 已经访问过，剪枝
        if (board[x][y] != word[index]) return false; // 不相等，剪枝
        visited[x][y] = true;
        bool ret = dfs(board, word, index + 1, x - 1, y, visited) || // 上
                   dfs(board, word, index + 1, x + 1, y, visited) || // 下
                   dfs(board, word, index + 1, x, y - 1, visited) || // 左
                   dfs(board, word, index + 1, x, y + 1, visited); // 右
        visited[x][y] = false;
        return ret;
    }
};