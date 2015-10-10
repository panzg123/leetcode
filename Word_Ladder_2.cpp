class Solution {
public:
	/*递归 时间复杂度 O(n)，空间复杂度 O(n)*/
    vector<vector<string> > findLadders(string beginWord, string endWord,unordered_set<string> &wordList)
	{
		unordered_set<string> current, next; // 当前层，下一层，用集合是为了去重
		unordered_set<string> visited; // 判重
		unordered_map<string, vector<string> > father; // 树
		bool found = false;
		auto state_is_target = [&](const string &s)
		{
			return s == endWord;
		};
		auto state_extend = [&](const string &s)
		{
			unordered_set<string> result;
			for (size_t i = 0; i < s.size(); ++i)
			{
				string new_word(s);
				for (char c = 'a'; c <= 'z'; c++)
				{
					if (c == new_word[i]) continue;
					swap(c, new_word[i]);
					if ((wordList.count(new_word) > 0 || new_word == endWord) &&
						!visited.count(new_word))
					{
						result.insert(new_word);
					}
					swap(c, new_word[i]); // 恢复该单词
				}
			}
			return result;
		};
		current.insert(beginWord);
		while (!current.empty() && !found)
		{
			// 先将本层全部置为已访问，防止同层之间互相指向,互指导致距离出错
			for (const auto& word : current)
				visited.insert(word);
			for (const auto& word : current)
			{
				const auto new_states = state_extend(word);
				for (const auto &state : new_states)
				{
					if (state_is_target(state)) found = true;
					next.insert(state);
					//多个父节点
					father[state].push_back(word);
					// visited.insert(state); // 移动到最上面了
				}
			}
			current.clear();
			swap(current, next);
		}
		vector<vector<string> > result;
		if (found)
		{
			vector<string> path;
			gen_path(father, path, beginWord, endWord, result);
		}
		return result;
	}
	void gen_path(unordered_map<string, vector<string> > &father,
		vector<string> &path, const string &start, const string &word,
		vector<vector<string> > &result)
	{
		path.push_back(word);
		if (word == start)
		{
			result.push_back(path);
			//路径反转
			reverse(result.back().begin(), result.back().end());
		}
		else
		{
			for (const auto& f : father[word])
			{
			    //多个父节点
				gen_path(father, path, start, f, result);
			}
		}
		path.pop_back();
	}
};