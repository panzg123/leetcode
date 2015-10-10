class Solution {
public:
	/*Palindrome Partitioning 时间复杂度 O(2^n)，空间复杂度 O(n) 
	主要思想：一个长度为 n 的字符串，有 n ? 1 个地方可以砍断，每个地方可断可不断 */
	vector<vector<string>> partition(string s)
	{
		vector<vector<string>> result;
		vector<string> path; // 一个 partition 方案
		partition_help(s, path, result, 0, 1);
		return result;
	}
	// s[0, prev-1] 之间已经处理，保证是回文串
	// prev 表示 s[prev-1] 与 s[prev] 之间的空隙位置， start 同理
	void partition_help(string &s, vector<string> &path, vector<vector<string>> &result, size_t prev, size_t start)
	{
		if (start == s.size())
		{
			if (isPalindrome(s, prev, start - 1))
			{
				path.push_back(s.substr(prev, start - prev));
				result.push_back(path);
				path.pop_back();
			}
			return;
		}
		//dfs不断开
		partition_help(s, path, result, prev, start + 1);
		//如果[prev,start-1]是回文，则可以断开
		if (isPalindrome(s, prev, start - 1))
		{
			path.push_back(s.substr(prev, start - prev));
			partition_help(s, path, result, start, start + 1);
			path.pop_back();
		}
	}
	/*判断是否是回文，start和end表示起始和结束位置*/
	bool isPalindrome(const string &s, int start, int end)
	{
		while (start<end && s[start] == s[end])
		{
			++start;
			--end;
		}
		return start >= end;
	}
};