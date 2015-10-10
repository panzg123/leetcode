class Solution {
public:
	/*
	Letter Combinations of a Phone Number
	�ݹ飬 ʱ�临�Ӷ� O(3^n)���ռ临�Ӷ� O(n)
	*/
    vector<string> letterCombinations(string digits)
	{
		vector<string> result;
		if (digits == "") return result;
		letterCombinations_help(digits, 0, "", result);
		return result;
	}
	void letterCombinations_help(const string& digits,size_t cur,string path,vector<string> &result)
	{
		if (cur == digits.size())
		{
			result.push_back(path);
			return;
		}
		for (auto s : keyboard[digits[cur]-'0'])
		{
			letterCombinations_help(digits, cur + 1, path+s, result);
		}
		return;
	}
private:
	const vector<string> keyboard = { " ", "", "abc", "def", // '0','1','2',...
		"ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
};