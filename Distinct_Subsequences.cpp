class Solution {
public:
	/*Distinct Subsequences
	 二维动规 + 滚动数组,时间复杂度 O(m*n)，空间复杂度 O(n)
	 思路：设状态为 f(i, j)，表示 T[0,j] 在 S[0,i] 里出现的次数。
	 首先，无论 S[i] 和 T[j] 是否相等，若不使用 S[i]，则 f(i, j) = f(i − 1, j)；
	 若 S[i]==T[j]，则可以使用 S[i]，此时f(i, j) = f(i − 1, j) + f(i − 1, j − 1)。
	*/
    int numDistinct(string s, string t) {
        vector<int> f(t.size() + 1);
		f[0] = 1;
		for (int i = 0; i < s.size(); i++)
		{
			for (int j = t.size() - 1; j >= 0; --j)
				f[j + 1] += s[i] == t[j]?f[j]:0;
		}
		return f[t.size()];
    }
};