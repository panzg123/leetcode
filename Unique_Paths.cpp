class Solution {
public:
	/*Unique Paths ��̬�滮 ʱ�临�Ӷ� O(n^2)���ռ临�Ӷ� O(n)*/
	int uniquePaths(int m, int n)
	{
		const int MAX_LEN = 100;
		int dp[MAX_LEN][MAX_LEN];
		//��ʼ��
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
		//״̬ת�ƣ�f[i][j]=f[i-1][j]+f[i][j-1]
		for (size_t i = 1; i < m; i++)
		{
			for (size_t j = 1; j < n; j++)
			{
				dp[i][j] = (dp[i][j-1]+dp[i-1][j]);
			}
		}
		return dp[m - 1][n - 1];
	}
	/*DFS ʱ�临�Ӷ� O(n^4)���ռ临�Ӷ� O(n)*/
	int uniquePaths_DFS(int m, int n) {
		if (m < 1 || n < 1) return 0; // ��ֹ����
		if (m == 1 && n == 1) return 1; // ��������
		return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
	}
};