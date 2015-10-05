class Solution
{
public:
	/*
	Anagrams
	problem:Given an array of strings, return all groups of strings that are anagrams.
	analysis:单词里的字母的种类和数目没有改变，只是改变了字母的排列顺序。 因此，将几个单词按照字母顺序排序后，若它们相等，则它们属于同一组 anagrams 。
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
	/*valid anagram , 判断两个字符串是不是anagram*/
	bool isAnagram(string s, string t)
	{
		sort(s.begin(), s.end());
		sort(t.begin(), t.end());
		if (s == t) return true;
		else return false;
	}
}