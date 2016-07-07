//乐视2017实习生在线编程，编程题：困兽之斗
//并查集
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <algorithm>

//using namespace std;

#define MAX 10001   //自己设置最大值

// father[x]表示x的父节点
int father[MAX];
// rank[x]表示x的秩
int rank[MAX];

// 初始化
void Make_Set(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		father[i] = i;
		rank[i] = 0;
	}
}

// 查找
int Find_Set(int x)
{
	if (x != father[x])
		return Find_Set(father[x]);
	return x;
}

// 合并
void Union(int x, int y)
{
	x = Find_Set(x);
	y = Find_Set(y);
	if (x == y)  // x,y在同一个集合
		return;
	if (rank[x] > rank[y])
		father[y] = x;
	else if (rank[x] < rank[y])
		father[x] = y;
	else
	{
		rank[y]++;
		father[x] = y;
	}
}

int N, M;
int main()
{
	std::string str;
	int a, b;
	while (std::cin >> str)
	{
		//first为顶层的father节点，msets中记录该father节点下的全部节点
		std::unordered_map<int, std::vector<char>> msets;
		//first为顶层的father节点,vector中记录相应节点的位置
		std::unordered_map<int, std::vector<int>> midxs;
		N = str.length();
		for (int i = 1; i <= N; ++i)
			Make_Set(i);
		std::cin >> M;
		while (M--)
		{
			std::cin >> a >> b;
			Union(a+1, b+1);
		}
		int cnt = -1;
		for (int i = 1; i <= N; ++i)
		{
			int idx = Find_Set(i);
			msets[idx].push_back(str[i-1]);
			midxs[idx].push_back(i-1);
		}

		for (auto it = msets.begin(); it != msets.end(); ++it)
		{
			std::vector<char> char_vec = it->second;
			std::vector<int> idx = midxs[it->first];
			//字符序，排序
			std::sort(char_vec.begin(), char_vec.end());
			//排序后赋值
			for (int i = 0; i < char_vec.size();i++)
			{
				str[idx[i]] = char_vec[i];
			}
		}
		std::cout << str << std::endl;
	}
	return 0;
}