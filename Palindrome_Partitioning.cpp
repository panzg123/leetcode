class Solution {
public:
	/*Palindrome Partitioning ʱ�临�Ӷ� O(2^n)���ռ临�Ӷ� O(n) 
	��Ҫ˼�룺һ������Ϊ n ���ַ������� n ? 1 ���ط����Կ��ϣ�ÿ���ط��ɶϿɲ��� */
	vector<vector<string>> partition(string s)
	{
		vector<vector<string>> result;
		vector<string> path; // һ�� partition ����
		partition_help(s, path, result, 0, 1);
		return result;
	}
	// s[0, prev-1] ֮���Ѿ�������֤�ǻ��Ĵ�
	// prev ��ʾ s[prev-1] �� s[prev] ֮��Ŀ�϶λ�ã� start ͬ��
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
		//dfs���Ͽ�
		partition_help(s, path, result, prev, start + 1);
		//���[prev,start-1]�ǻ��ģ�����ԶϿ�
		if (isPalindrome(s, prev, start - 1))
		{
			path.push_back(s.substr(prev, start - prev));
			partition_help(s, path, result, start, start + 1);
			path.pop_back();
		}
	}
	/*�ж��Ƿ��ǻ��ģ�start��end��ʾ��ʼ�ͽ���λ��*/
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