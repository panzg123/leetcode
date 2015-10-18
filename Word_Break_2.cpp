/*word Break 2 动规，时间复杂度 O(n^2)，空间复杂度 O(n^2)
	设状态为 f(i)，表示 s[0,i] 是否可以分词，则状态转移方程为 f(i) = any_of(f(j)&&s[j + 1, i] ∈ dict),0 ≤ j < i
	*/
	vector<string> wordBreak2(string s, unordered_set<string> &dict)
	{
		vector<string> result;
		vector<string> path;
		if (dict.size() == 0) return result;
		vector<bool> f(s.length() + 1, false);
		vector<vector<bool>> prev(s.length() + 1, vector<bool>(s.length()));
		f[0] = true;
		for (int i = 1; i <=s.length(); ++i)
		{
			for (int j = i-1; j>=0; --j)
			{
				if (f[j] && dict.find(s.substr(j, i - j)) != dict.end())
				{
					f[i] = true;
					prev[i][j] = true;
				}
			}
		}
		wordbreak_genpath(s, prev, s.length(), path, result);
		return result;
	}
	//辅助函数，生成路径，DFS
	void wordbreak_genpath(const string &s, const vector<vector<bool>> &prev, int cur, vector<string> &path, vector<string> &result)
	{
		if (cur == 0)
		{
			string tmp;
			//反转
			for (auto iter = path.crbegin(); iter != path.crend();++iter)
			{
				tmp += *iter + " ";
			}
			//删除最后的一个空格
			tmp.erase(tmp.end() - 1);
			result.push_back(tmp);
		}
		for (size_t i = 0; i < s.size(); i++)
		{
			if (prev[cur][i])
			{
				path.push_back(s.substr(i, cur - i));
				wordbreak_genpath(s, prev, i, path, result);
				path.pop_back();
			}
		}
	}