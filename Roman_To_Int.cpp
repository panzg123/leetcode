class Solution {
public:
	/*
	ǰ����ɨ�裬��һ����ʱ������¼�ֶ����֡�
	�����ǰ��ǰһ����˵����һ�ε�ֵӦ���ǵ�ǰ���ֵ��ȥ��һ��ֵ��
	*/
	int romanToInt(string s)
	{
		map<char, int> roman = { { 'I', 1 }, { 'V', 5 }, { 'X', 10 }, { 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };
		int sum = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (i>0 && roman[s[i]] > roman[s[i - 1]])
				sum += (roman[s[i]] - 2 * roman[s[i - 1]]); /*ǰһλ��ֵ�����㣬��Ҫ��ȥ*/
			else
				sum += roman[s[i]];
		}
		return sum;
	}
};