class Solution {
public:
	/*
	模拟
	题意是n=1时输出字符串1；n=2时，数上次字符串中的数值个数，因为上次字符串有1个1，所以输出11；
	n=3时，由于上次字符是11，有2个1，所以输出21；n=4时，由于上次字符串是21，有1个2和1个1，所以输出1211。依次类推。
	*/
	string countAndSay(int n)
	{
		string s = "1";
		while (--n)
			s=getNext(s);
		return s;
	}
	string getNext(const string &s)
	{
		std::stringstream ss;
		for (auto i = s.begin(); i != s.end();)
		{
			auto j = find_if(i, s.end(), bind1st(not_equal_to<char>(),*i));
			ss << distance(i, j) << *i;
			i = j;
		}
		return ss.str();
	}
};