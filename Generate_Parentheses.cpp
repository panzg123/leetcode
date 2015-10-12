class Solution {
public:
	/*Generate Parentheses 先用next_premutation生成全排列，然后再判断该排列是否有效*/
    vector<string> generateParenthesis(int n)
	{
		vector<string> result;
		string s(n, '(');
		string s1(n, ')');
		s += s1;
		
		sort(s.begin(), s.end());
		do
		{
			if (parentheses_Valid(s))
			{
				result.push_back(s);
			}
		} while (std::next_permutation(s.begin(), s.end()));
		return result;
	}
	/*判断括号匹配是否有效*/
	bool parentheses_Valid(string s)
	{
		stack<char> stack_char;
		int i = 0;
		while (i<s.size())
		{
			if (s[i] == '(')
				stack_char.push('(');
			else
			{
				if (!stack_char.empty())
					stack_char.pop();
				else return false;
			}
			i++;
		}
		return true;
	}
	/*递归，小括号串是一个递归结构，跟单链表、二叉树等递归结构一样，首先想到用递归*/
	vector<string> generateParenthesis_v2(int n) 
	{
		vector<string> result;
		if (n > 0) generate(n, "", 0, 0, result);
		return result;
	}
	// l 表示 '(' 出现的次数, r 表示 ')' 出现的次数
	void generate(int n, string s, int l, int r, vector<string> &result)
	{
		if (l == n)
		{
			result.push_back(s.append(n - r, ')'));
			return;
		}
		generate(n, s + '(', l + 1, r, result);
		if (l > r) generate(n, s + ")", l, r + 1, result);
	}
};