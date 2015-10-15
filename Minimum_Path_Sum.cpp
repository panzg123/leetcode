class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
		int m = grid[0].size();
		vector<vector<int>> path(n, vector<int>(m, 0));

        path[0][0] = grid[0][0];
		for (size_t i = 1; i < n; i++)
		{
			path[i][0] = path[i - 1][0] + grid[i][0];
		}
		for (size_t i = 1; i < m; i++)
		{
			path[0][i] = path[0][i-1] + grid[0][i];
		}

		for (size_t i = 1; i < n; i++)
		{
			for (size_t j = 1; j < m; j++)
			{
				path[i][j] = min(path[i - 1][j], path[i][j - 1]) + grid[i][j];
			}
		}
		return path[n - 1][m - 1];
    }
};