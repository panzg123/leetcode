class Solution {
public:
	/*Word Ladder ����������� ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(n) */
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        queue<string> current, next; // ��ǰ�㣬��һ��
		unordered_set<string> visited; // ����
		int level = 0; // ���
		bool found = false;
		//�ж��Ƿ񵽴��յ�
		auto state_is_target = [&](const string &s)
		{
			return s == endWord;
		};
		//��ȡ����s���Ե���ĵ��ʼ���
		auto state_extend = [&](const string &s)
		{
			vector<string> result;
			for (size_t i = 0; i < s.size(); ++i)
			{
				string new_word(s);
				//�ı�һ����ĸ
				for (char c = 'a'; c <= 'z'; c++)
				{
					if (c == new_word[i]) continue;
					swap(c, new_word[i]);
					//��Ҫ��֤����δ�����ʹ�
					if ((wordList.count(new_word) > 0 || new_word == endWord) &&
						!visited.count(new_word))
					{
						result.push_back(new_word);
						visited.insert(new_word);
					}
					swap(c, new_word[i]); // �ָ��õ���
				}
			}
			return result;
		};
		current.push(beginWord);
		//found����Ƿ��ҵ�
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
						found = true; //�ҵ��ˣ��˳�
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