class Solution {
public:
	/*�ݹ� ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(n)*/
    vector<vector<string> > findLadders(string beginWord, string endWord,unordered_set<string> &wordList)
	{
		unordered_set<string> current, next; // ��ǰ�㣬��һ�㣬�ü�����Ϊ��ȥ��
		unordered_set<string> visited; // ����
		unordered_map<string, vector<string> > father; // ��
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
					swap(c, new_word[i]); // �ָ��õ���
				}
			}
			return result;
		};
		current.insert(beginWord);
		while (!current.empty() && !found)
		{
			// �Ƚ�����ȫ����Ϊ�ѷ��ʣ���ֹͬ��֮�以��ָ��,��ָ���¾������
			for (const auto& word : current)
				visited.insert(word);
			for (const auto& word : current)
			{
				const auto new_states = state_extend(word);
				for (const auto &state : new_states)
				{
					if (state_is_target(state)) found = true;
					next.insert(state);
					//������ڵ�
					father[state].push_back(word);
					// visited.insert(state); // �ƶ�����������
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
			//·����ת
			reverse(result.back().begin(), result.back().end());
		}
		else
		{
			for (const auto& f : father[word])
			{
			    //������ڵ�
				gen_path(father, path, start, f, result);
			}
		}
		path.pop_back();
	}
};