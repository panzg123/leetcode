//��Ѷ2017����ʵϰ�������
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

//��Ŀ��СQ���������һ�����⣺��һ���ַ����Ĵ�д��ĸ�ŵ��ַ����ĺ��棬�����ַ������λ�ò��䣬�Ҳ����������Ŀռ䡣���ܰ��СQ��
//���ӣ�AkleBiCeilD --> kleieilABCD
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




//��Ŀ��СQ�������ϲ���ʱ�뵽��������⣺��n������������ɶ�Ԫ�飬��ľ���ֵ��С���ж��ٶ��أ���ľ���ֵ�����أ�
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
		//������
		sort(dat.begin(), dat.end());
		int num_min = 0;
		int val_min = INT_MAX;
		int pre_idx = 0;
		for (int i = 1; i < number;i++)
		{
			int dis = dat[i] - dat[i - 1];
			if (dis == val_min)
			{
				//���ǰN������ͬ
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
		//���ȫ�����ݶ�һ��
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

//��Ŀ������һ���ַ���s������Դ���ɾ��һЩ�ַ���ʹ��ʣ�µĴ���һ�����Ĵ������ɾ������ʹ�û��Ĵ���أ������Ҫɾ�����ַ�������
//˼·����ԭ�ַ������䷴������󹫹��Ӵ��ĳ��ȣ�Ȼ����ԭ�ַ����ĳ��ȼ�ȥ�����󹫹��Ӵ��ĳ��Ⱦ͵õ�����С�༭���ȡ�
void question3()
{
	//�������������
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