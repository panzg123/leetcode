class Solution {
public:
	/*Unique Paths 动态规划 时间复杂度 O(n^2)，空间复杂度 O(n)*/
	int uniquePaths(int m, int n)
	{
		const int MAX_LEN = 100;
		int dp[MAX_LEN][MAX_LEN];
		//初始化
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				dp[i][j] = 0;
			}
		}
		for (size_t i = 0; i < n; i++)
		{
			dp[0][i] = 1;
		}
		for (size_t i = 0; i < m; i++)
		{
			dp[i][0] = 1;
		}
		//状态转移：f[i][j]=f[i-1][j]+f[i][j-1]
		for (size_t i = 1; i < m; i++)
		{
			for (size_t j = 1; j < n; j++)
			{
				dp[i][j] = (dp[i][j-1]+dp[i-1][j]);
			}
		}
		return dp[m - 1][n - 1];
	}
	/*DFS 时间复杂度 O(n^4)，空间复杂度 O(n)*/
	int uniquePaths_DFS(int m, int n) {
		if (m < 1 || n < 1) return 0; // 终止条件
		if (m == 1 && n == 1) return 1; // 收敛条件
		return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
	}
};