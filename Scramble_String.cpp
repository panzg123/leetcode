class Solution {
public:
    /*Scramble String ,dp，时间复杂度 O(n^3)，空间复杂度 O(n^3)
	设状态为 f[n][i][j]，表示长度为 n，起点为 s1[i] 和起点为 s2[j] 两个字符串是否互为 scramble，
	则状态转移方程为 f[n][i][j]} = (f[k][i][j] && f[n-k][i+k][j+k]) || (f[k][i][j+n-k] && f[n-k][i+k][j])
	*/
	bool isScramble(string s1, string s2)
	{
		const int MAX_LEN = 100;
		const int N = s1.size();
		if (N != s2.size()) return false;
		// f[n][i][j]，表示长度为 n，起点为 s1[i] 和
		// 起点为 s2[j] 两个字符串是否互为 scramble
		bool f[MAX_LEN + 1][MAX_LEN][MAX_LEN];
		fill_n(&f[0][0][0], (MAX_LEN + 1)*MAX_LEN*MAX_LEN, false);
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				f[1][i][j] = s1[i]==s2[j];
			}
		}
		for (size_t n = 1; n <= N; n++)
		{
			for (int i = 0; i + n <= N; ++i)
			{
				for (int j = 0; j + n <= N; ++j)
				{
					for (int k = 1; k < n; ++k)
					{
						if ((f[k][i][j] && f[n - k][i + k][j + k]) ||
							(f[k][i][j + n - k] && f[n - k][i + k][j]))
						{
							f[n][i][j] = true;
							break;
						}
					}
				}
			}
		}
		return f[N][0][0];
	}
};