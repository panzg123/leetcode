class Solution {
public:
	/*Decode ways, DP
	当前位置的状态和前两个位置的状态有关，如果能和前一个字符组合，则为f[i-2]+f[i-1],不能组合为f[n-1]
	*/
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
		int prev = 0;
		int cur = 1;
		// 长度为 n 的字符串，有 n+1 个阶梯
		for (size_t i = 1; i <= s.size(); ++i) 
		{
			if (s[i - 1] == '0') cur = 0;
			if (i < 2 || !(s[i - 2] == '1' ||
				(s[i - 2] == '2' && s[i - 1] <= '6')))
				prev = 0;
			int tmp = cur;
			cur = prev + cur;
			prev = tmp;
		}
		return cur;
    }
};