class Solution {
public:
	/*Unique Paths 2 动态规划 时间复杂度 O(n^2)，空间复杂度 O(n)*/
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
	{
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		const int MAX_LEN = 100;
		int dp[MAX_LEN][MAX_LEN];
		//初始化
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				dp[i][j] = (obstacleGrid[i][j]==1?0:1);
			}
		}
		
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				//第0行，状态转移：f[i][j]=f[i][j-1]
				if (i == 0 && j>0 && obstacleGrid[i][j]==0)
					dp[0][j] = dp[0][j - 1];
				//第0列，状态转移：f[i][j]=f[i-1][j]
				if (j == 0 && i>0 && obstacleGrid[i][j]==0)
					dp[i][0] = dp[i - 1][0];
				//状态转移：f[i][j]=f[i-1][j]+f[i][j-1]
				if (obstacleGrid[i][j]!=1 && i>0 && j>0)
					dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]);
			}
		}
		return dp[m - 1][n - 1];
	}
};