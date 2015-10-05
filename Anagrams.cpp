class Solution
{
public:
	/*
	Anagrams
	problem:Given an array of strings, return all groups of strings that are anagrams.
	analysis:���������ĸ���������Ŀû�иı䣬ֻ�Ǹı�����ĸ������˳�� ��ˣ����������ʰ�����ĸ˳���������������ȣ�����������ͬһ�� anagrams ��
	*/
	vector<string> anagrams(vector<string> &strs)
	{
		unordered_map<string, vector<string>> group;
		for (const auto &s : strs)
		{
			string key = s;
			sort(key.begin(), key.end());
			group[key].push_back(s);
		}
		vector<string> result;
		for (auto it = group.cbegin(); it != group.cend(); it++)
		{
			if (it->second.size() > 1)
				result.insert(result.end(), it->second.begin(), it->second.end());
		}
		return result;
	}
	/*Group Anagrams*/
	vector<vector<string>> groupAnagrams(vector<string>& strs)
	{
		unordered_map<string, vector<string>> group;
		for (const auto &s : strs)
		{
			string key = s;
			sort(key.begin(), key.end());
			group[key].push_back(s);
		}
		vector<vector<string>> result;
		for (auto it = group.cbegin(); it != group.cend(); it++)
		{
			vector<string> temp = it->second;
			sort(temp.begin(), temp.end());
			result.push_back(temp);
		}
		return result;
	}
	/*valid anagram , �ж������ַ����ǲ���anagram*/
	bool isAnagram(string s, string t)
	{
		sort(s.begin(), s.end());
		sort(t.begin(), t.end());
		if (s == t) return true;
		else return false;
	}
}