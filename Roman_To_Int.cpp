class Solution {
public:
	/*
	前往后扫描，用一个临时变量记录分段数字。
	如果当前比前一个大，说明这一段的值应该是当前这个值减去上一个值。
	*/
	int romanToInt(string s)
	{
		map<char, int> roman = { { 'I', 1 }, { 'V', 5 }, { 'X', 10 }, { 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };
		int sum = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (i>0 && roman[s[i]] > roman[s[i - 1]])
				sum += (roman[s[i]] - 2 * roman[s[i - 1]]); /*前一位的值被计算，需要减去*/
			else
				sum += roman[s[i]];
		}
		return sum;
	}
};