class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
       // 长度为 n 的字符串有 n+1 个隔板
		vector<bool> f(s.size() + 1, false);
		f[0] = true; // 空字符串
		for (int i = 1; i <= s.size(); ++i) 
		{
			for (int j = i - 1; j >= 0; --j)
			{
				if (f[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end())
				{
					f[i] = true;
					break;
				}
			}
		}
		return f[s.size()];
    }
};