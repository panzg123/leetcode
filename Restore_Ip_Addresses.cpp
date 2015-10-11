class Solution {
public:
    /*Restore IP Addresses 时间复杂度 O(n^4)，空间复杂度 O(n)*/
	vector<string> restoreIpAddresses(string s)
	{
		vector<string> result;
		string ip; // 存放中间结果
		restoreIpAddresses_dfs(s, 0, 0, ip, result);
		return result;
	}
	/**
	* @brief 解析字符串
	* @param[in] s 字符串，输入数据
	* @param[in] startIndex 从 s 的哪里开始
	* @param[in] step 当前步骤编号，从 0 开始编号，取值为 0,1,2,3,4 表示结束了
	* @param[out] intermediate 当前解析出来的中间结果
	* @param[out] result 存放所有可能的 IP 地址
	* @return 无
	*/
	void restoreIpAddresses_dfs(string s, size_t start, size_t step, string ip,
		vector<string> &result)
	{
		if (start == s.size() && step == 4)   // 找到一个合法解
		{
			ip.resize(ip.size() - 1);
			result.push_back(ip);
			return;
		}
		if (s.size() - start > (4 - step) * 3)
			return; // 剪枝
		if (s.size() - start < (4 - step))
			return; // 剪枝
		int num = 0;
		for (size_t i = start; i < start + 3; i++)
		{
			num = num * 10 + (s[i] - '0');
			if (num <= 255)   // 当前结点合法，则继续往下递归
			{
				ip += s[i];
				restoreIpAddresses_dfs(s, i + 1, step + 1, ip + '.', result);
			}
			if (num == 0) break; // 不允许前缀 0，但允许单个 0
		}
	}
};