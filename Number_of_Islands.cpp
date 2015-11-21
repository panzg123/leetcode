/*两种方法，并查集，DFS*/
class Solution
{
public:
#define MAX 100000
    /* father[x]表示x的父节点 */
    int father[MAX];
    /* rank[x]表示x的秩 */
    int rank[MAX];

    /* 初始化集合 */
    void Make_Set(int x)
    {
        father[x] = x;
        rank[x] = 0;
    }

    /* 查找x元素所在的集合,回溯时压缩路径 */
    int Find_Set(int x)
    {

        if (x != father[x])
        {
            father[x] = Find_Set(father[x]);
        }
        return father[x];
    }

    /* 按秩合并x,y所在的集合 */
    void Union(int x, int y)
    {
        x = Find_Set(x);
        y = Find_Set(y);
        if (x == y) return;
        if (rank[x] > rank[y])
        {
            father[y] = x;
        }
        else
        {
            if (rank[x] == rank[y])
            {
                rank[y]++;
            }
            father[x] = y;
        }
    }
    /*Number of Islands 并查集*/
    int numIslands(vector<vector<char>>& grid)
    {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        for (int i = 0; i < m*n; ++i)
            Make_Set(i);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == '1')
                {
                    //上
                    if (i>0 && grid[i - 1][j] == '1')
                        Union(i*n + j, (i - 1)*n + j);
                    //左
                    if (j>0 && grid[i][j-1] == '1')
                        Union(i*n + j, i*n + j-1);
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < m*n; i++)
        {
            if (grid[i/n][i%n]=='1' && father[i] == i)
                cnt++;
        }
        return cnt;
    }
    /*Number of Islands,DFS*/
    int numIslands_dfs(vector<vector<char>>& grid)
    {
        if (grid.size() == 0) return 0;
        int numIld = 0;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == '1')
                {
                    numIld++;
                    dfs(i, j, grid);
                }
            }
        }
        return numIld;
    }
    void dfs(int i, int j, vector<vector<char>>& grid)
    {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0') return;
        grid[i][j] = '0';
        dfs(i + 1, j, grid);
        dfs(i, j + 1, grid);
        dfs(i - 1, j, grid);
        dfs(i, j - 1, grid);
    }
};