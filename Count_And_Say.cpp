class Solution {
public:
	/*
	ģ��
	������n=1ʱ����ַ���1��n=2ʱ�����ϴ��ַ����е���ֵ��������Ϊ�ϴ��ַ�����1��1���������11��
	n=3ʱ�������ϴ��ַ���11����2��1���������21��n=4ʱ�������ϴ��ַ�����21����1��2��1��1���������1211���������ơ�
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