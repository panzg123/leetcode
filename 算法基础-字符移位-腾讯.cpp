//腾讯2017暑期实习生编程题
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

//题目：小Q最近遇到了一个难题：把一个字符串的大写字母放到字符串的后面，各个字符的相对位置不变，且不能申请额外的空间。你能帮帮小Q吗？
//例子：AkleBiCeilD --> kleieilABCD
int question1()
{
	string str;
	while (cin >> str)
	{
		int count = 1;
		for (int i = str.size() - 1; i >= 0; i--)
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				char temp = str[i];
				int j = 0;
				for (j = i; j < str.size() - count; j++)
				{
					str[j] = str[j + 1];
				}
				str[j] = temp;
				count++;
			}
		}
		cout << str << endl;
	}
	return 0;
}




//题目：小Q今天在上厕所时想到了这个问题：有n个数，两两组成二元组，差的绝对值最小的有多少对呢？差的绝对值最大的呢？
int question2()
{
	int number;
	while (cin >> number && number)
	{
		if (number == 1)
			cout << "0 0" << endl;
		vector<int> dat;
		int temp;
		for (int i = 0; i < number;i++)
		{
			cin >> temp;
			dat.push_back(temp);
		}
		//先排序
		sort(dat.begin(), dat.end());
		int num_min = 0;
		int val_min = INT_MAX;
		int pre_idx = 0;
		for (int i = 1; i < number;i++)
		{
			int dis = dat[i] - dat[i - 1];
			if (dis == val_min)
			{
				//如果前N个数相同
				num_min +=(i-pre_idx);
			}
			else if (dis < val_min)
			{
				num_min = 1;
				val_min = dis;
			}
			if (dat[i] != dat[i - 1])
				pre_idx = i;
		}
		//如果全部数据都一样
		if (dat[0] == dat[number-1])
			cout << num_min << " " << number*(number-1)/2 << endl;
		else
		{
			int count_min_ele = count(dat.begin(), dat.end(), dat[0]);
			int count_max_ele = count(dat.begin(), dat.end(), dat[number - 1]);
			cout << num_min << " " << count_min_ele*count_max_ele << endl;
		}
	}
	return 0;
}

//题目：给定一个字符串s，你可以从中删除一些字符，使得剩下的串是一个回文串。如何删除才能使得回文串最长呢？输出需要删除的字符个数。
//思路：求原字符串和其反串的最大公共子串的长度，然后用原字符串的长度减去这个最大公共子串的长度就得到了最小编辑长度。
void question3()
{
	//求最长公共子序列
	auto lcs_func = [](string str1, string str2)
	{
		vector<vector<int>> dp(str1.size(), vector<int>(str2.size(), 0));
		dp[0][0] = str1[0] == str2[0] ? 1 : 0;
		for (int i = 1; i < str1.length(); i++)
		{
			dp[i][0] = max(dp[i - 1][0], str1[i] == str2[0] ? 1 : 0);
		}
		for (int j = 1; j < str2.length(); j++)
		{
			dp[0][j] = max(dp[0][j - 1], str1[0] == str2[j] ? 1 : 0);
		}
		for (int i = 1; i < str1.length(); i++)
		{
			for (int j = 1; j < str2.length(); j++)
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				if (str1[i] == str2[j])
				{
					dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
				}
			}
		}
		return dp[str1.size() - 1][str2.size() - 1];
	};
	string str;
	while (cin>>str)
	{
		string reverse_str = str;
		reverse(reverse_str.begin(), reverse_str.end());
		int lcs_len = lcs_func(str, reverse_str);
		cout << str.size() - lcs_len << endl;
	}
}

#if 0
int main()
{
	question3();
	return 0;
}
#endif