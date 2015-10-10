class Solution {
public:
	/*Word Ladder 广度优先搜索 时间复杂度 O(n)，空间复杂度 O(n) */
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        queue<string> current, next; // 当前层，下一层
		unordered_set<string> visited; // 判重
		int level = 0; // 层次
		bool found = false;
		//判断是否到达终点
		auto state_is_target = [&](const string &s)
		{
			return s == endWord;
		};
		//获取单词s可以到达的单词集合
		auto state_extend = [&](const string &s)
		{
			vector<string> result;
			for (size_t i = 0; i < s.size(); ++i)
			{
				string new_word(s);
				//改变一个字母
				for (char c = 'a'; c <= 'z'; c++)
				{
					if (c == new_word[i]) continue;
					swap(c, new_word[i]);
					//需要保证单词未被访问过
					if ((wordList.count(new_word) > 0 || new_word == endWord) &&
						!visited.count(new_word))
					{
						result.push_back(new_word);
						visited.insert(new_word);
					}
					swap(c, new_word[i]); // 恢复该单词
				}
			}
			return result;
		};
		current.push(beginWord);
		//found标记是否找到
		while (!current.empty() && !found)
		{
			++level;
			while (!current.empty() && !found)
			{
				const string str = current.front();
				current.pop();
				const auto& new_states = state_extend(str);
				for (const auto& state : new_states)
				{
					next.push(state);
					if (state_is_target(state))
					{
						found = true; //找到了，退出
						break;
					}
				}
			}
			swap(next, current);
		}
		if (found) return level + 1;
		else return 0;
    }
};