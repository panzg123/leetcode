class Solution {
public:
    /*Interleaving String
	二维动规，时间复杂度 O(n^2)，空间复杂度 O(n^2)，
	设状态 f[i][j]，表示 s1[0,i] 和 s2[0,j]，匹配 s3[0, i+j]。如果 s1 的最后一个字符等于 s3 的最后一个字符，则 f[i][j]=f[i-1][j]；
	如果 s2 的最后一个字符等于 s3 的最后一个字符，则 f[i][j]=f[i][j-1]。
	因此状态转移方程如下：
	f[i][j] = (s1[i - 1] == s3 [i + j - 1] && f[i - 1][j]) || (s2[j - 1] == s3 [i + j - 1] && f[i][j - 1]);
	也可以用DFS，但会超时*/
	bool isInterleave(string s1, string s2, string s3) 
	{
		if (s3.length() != s1.length() + s2.length())
			return false;
		vector<vector<bool>> f(s1.length() + 1,
			vector<bool>(s2.length() + 1, true));
		for (size_t i = 1; i <= s1.length(); ++i)
			f[i][0] = f[i - 1][0] && s1[i - 1] == s3[i - 1];
		for (size_t i = 1; i <= s2.length(); ++i)
			f[0][i] = f[0][i - 1] && s2[i - 1] == s3[i - 1];
		for (size_t i = 1; i <= s1.length(); ++i)
			for (size_t j = 1; j <= s2.length(); ++j)
				f[i][j] = (s1[i - 1] == s3[i + j - 1] && f[i - 1][j])
					|| (s2[j - 1] == s3[i + j - 1] && f[i][j - 1]);
		return f[s1.length()][s2.length()];
	}
};