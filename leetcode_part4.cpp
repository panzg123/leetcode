#include"header.h"
using namespace std;
namespace panzg_leetcode
{
	class Solution
	{
	public:
		/*Course Schedule II*/
		vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites)
		{
			vector<int> in_degree(numCourses, 0); //存储入度
			vector<unordered_set<int>> matrix(numCourses);//存储图
			vector<int> res;

			for (int i = 0; i < prerequisites.size(); i++)
			{
				matrix[prerequisites[i].second].insert(prerequisites[i].first);
			}
			//计算入度
			for (int i = 0; i < numCourses; i++)
			{
				for (auto it = matrix[i].begin(); it != matrix[i].end(); it++)
				{
					in_degree[*it]++;
				}
			}
			stack<int> zeor_degree_stack;//存储入度为0的节点
			int count = 0;//入度0的节点计数器
			for (int i = 0; i < numCourses; i++)
			{
				if (in_degree[i] == 0)
				{
					zeor_degree_stack.push(i);
					count++; //入度为0，计数加1
					res.push_back(i);
				}
			}
			//循环抽取入度为0的节点
			while (!zeor_degree_stack.empty())
			{
				int top = zeor_degree_stack.top();
				zeor_degree_stack.pop();
				for (auto it = matrix[top].begin(); it != matrix[top].end(); it++)
				{
					in_degree[*it]--;
					if (in_degree[*it] == 0)
					{
						zeor_degree_stack.push(*it);
						count++;
						res.push_back(*it);
					}
				}
			}
			if (count == numCourses)
				return res;
			else
			{
				vector<int> tmp; return tmp;
			}
		}
		/*Different Ways to Add Parentheses,递归*/
		vector<int> diffWaysToCompute(string input)
		{
			int length = input.size();
			vector<int> res;
			for (int i = 0; i < length; i++)
			{
				char c = input[i];
				//操作符
				if (ispunct(c))
				{
					vector<int> l_res = diffWaysToCompute(input.substr(0, i)); //左端结果
					vector<int> r_res = diffWaysToCompute(input.substr(i + 1)); //右端结果
					//组合
					for (int j = 0; j < l_res.size(); j++)
					{
						for (int k = 0; k < r_res.size(); k++)
						{
							switch (c)
							{
							case '+':
								res.push_back(l_res[j] + r_res[k]);
								break;
							case '-':
								res.push_back(l_res[j] - r_res[k]);
								break;
							case '*':
								res.push_back(l_res[j] * r_res[k]);
								break;
							default:
								break;
							}
						}
					}
				}

			}
			//字符串转化为数字
			if (res.empty())
				res.push_back(stoi(input));
			return res;
		}
		//Contains Duplicate
		bool containsDuplicate(vector<int>& nums)
		{
			unordered_map<int, int> map_;
			for (int i = 0; i < nums.size();i++)
			{
				auto it = map_.find(nums[i]);
				if (it != map_.end())
					return true;
				else
					map_[nums[i]] = 1;
			}
			return false;
		}
		//Shortest Palindrome,直接循环判断，超时
		string shortestPalindrome(string s)
		{
			string temp;
			int index = s.length();
			//从字符串末尾查找，最长的回文串
			while (index>1)
			{
				temp.assign(s, 0, index);
				if (is_palindrome(temp))
					break;
				else
					index--;
			}
			//找到最长回文串，构造结果
			if (index != s.length())
				temp.assign(s, index, string::npos);
			else
				return s;
			reverse(temp.begin(), temp.end());
			temp += s;
			return temp;
		}
		//判断是否回文
		bool is_palindrome(string s)
		{
			if (s.length() == 1)
				return true;
			int i=0,j=s.length()-1;
			while (i<j)
			{
				if (s[i] != s[j])
					return false;
				else
				{
					i++;
					j--;
				}
			}
			return true;
		}
		//Shortest Palindrome,kmp匹配法，具体可以参考讲解：https://leetcode.com/discuss/64309/clean-kmp-solution-with-super-detailed-explanation
		string shortestPalindrome_kmp(string s)
		{
			//先构造字符串:s+"#"+reverse(s),比如catacb的构造结果为：catacb # bcatac，保存到temp
			string temp = s;
			string str_res;
			temp += "#";
			string temp2 = s;
			reverse(temp2.begin(), temp2.end());
			temp += temp2;
			//获取kmp表
			vector<int> res(temp.size(), 0);
			kmp_get_next(temp, res);
			//取得最kmp末尾的值
			int index = res[temp.size() - 1];
			if (index != s.length()-1)
				str_res.assign(s, index+1, string::npos);
			else
				return s;
			reverse(str_res.begin(), str_res.end());
			//存储结果
			str_res += s;
			return str_res;
		}
		//kmp table，时间复杂度为O(N)，返回结果存储在next中
		void kmp_get_next(string s, vector<int>& next)
		{
			int length = s.size();
			int j = 1, k = 0;
			next[0] = -1;
			next[1] = 0;
			while (j<length-1)
			{
				if (s[j] == s[k])
				{
					j++;
					k++;
					next[j] = k;
				}
				else if (k == 0)
				{
					j++;
					next[j] = 0;
				}
				else
					k = next[k];
			}
		}
		//描述：kmp匹配，时间复杂度为O(N+M)
		//@src：主串
		//@start_pos:主串匹配起始位置
		//@dest:模式串
		//@kmp_table:kmp表，用kmp_get_next函数求得
		//@return:返回主串匹配的位置，无匹配则返回-1
		int kmp_match(string src,int start_pos,string dest,const vector<int>& kmp_table)
		{
			int i = start_pos;
			int j = 0;
			int res=0;
			while (i<src.length() && j<dest.length())
			{
				if (j == -1 || src[i] == dest[j]) //分别增加1
				{
					i++;
					j++;
				}
				else
					j = kmp_table[j]; //模式串右移
			}
			if (j == dest.length())
				res = i - dest.length();
			else
				res = -1;
			return res;
		}
		//Ugly Number,递归
		bool isUgly(int num) 
		{
			if (num == 1) return true;
			if (num == 0) return false;
			else if (num % 2 == 0) return isUgly(num / 2);
			else if (num % 3 == 0) return isUgly(num / 3);
			else if (num % 5 == 0) return isUgly(num / 5);
			else return false;
		}
		//string fractionToDecimal(int numerator, int denominator)
		//思路是用unordered_map来记录出现的数，如果重复出现，则是循环
		string fractionToDecimal(int numerator, int denominator)
		{
			string result;
			if (numerator == 0)
				return "0";
			if (denominator == 0)
				return "";
			//异号
			if ((numerator < 0) ^ (denominator < 0))
				result += "-";
			long long a = abs((long long)numerator);
			long long b = abs((long long)denominator);
			//求得整数部分
			result += to_string(abs(a) / abs(b));
			if (numerator%denominator == 0)
				return result;
			result += ".";
			//求小数部分
			unordered_map<int, int> map;
			for (long long r = a%b; r; r %= b)
			{
				if (map.count(r) > 0)
				{
					//在数r位置的前面插入'('
					result.insert(map[r], 1, '(');
					result += ")";
					break;
				}
				//保存数r出现的位置
				map[r] = result.size();
				r *= 10;
				result += to_string(r / b);
			}
			return result;
		}
		//Dungeon Game,动态规划，重点是从右下角开始循环
		int calculateMinimumHP(vector<vector<int>> &dungeon)
		{
			int row = dungeon.size();
			int col = dungeon[0].size();
			//res记录节点res[i][j]所需要的最少hp
			vector<vector<int>> res(row+1, vector<int>(col+1, INT_MAX));
			res[row - 1][col] = 1;
			res[row][col - 1] = 1;
			for (int i = row - 1; i >= 0; --i)
			{
				for (int j = col - 1; j >= 0; --j)
				{
					//选择右边或者下边中较小的hp值
					int t = min(res[i + 1][j], res[i][j + 1]) - dungeon[i][j];
					//最小为1
					res[i][j] = max(t, 1);
				}
			}
			//返回左上顶点需要的hp值
			return res[0][0];
		}
		//Kth Largest Element in an Array ,直接用排序,12ms
		int findKthLargest(vector<int>& nums, int k)
		{
			sort(nums.begin(), nums.end());
			return nums[nums.size() - k];
		}
		//Kth Largest Element in an Array ,堆,28ms,其它方法请参考：https://leetcode.com/discuss/36966/solution-explained
		int findKthLargest_v2(vector<int>& nums, int k)
		{
			vector<int> temp_vec = nums;
			make_heap(temp_vec.begin(), temp_vec.end());
			while (k > 1)
			{
				std::pop_heap(temp_vec.begin(), temp_vec.end()); 
				temp_vec.pop_back();
				k--;
			}
			return temp_vec.front();
		}

		void PrintfVectorInt(vector<int> &vet)
		{
			for (vector<int>::iterator pos = vet.begin(); pos != vet.end(); pos++)
				printf("%d ", *pos);
			putchar('\n');
		}
		int test_make_heap()
		{
			const int MAXN = 20;
			int a[MAXN];
			int i;
			for (i = 0; i < MAXN; ++i)
				a[i] = rand() % (MAXN * 2);

			//动态申请vector 并对vector建堆
			vector<int> *pvet = new vector<int>(40);
			pvet->assign(a, a + MAXN);

			//建堆
			make_heap(pvet->begin(), pvet->end());
			PrintfVectorInt(*pvet);

			//加入新数据 先在容器中加入，再调用push_heap()
			pvet->push_back(25);
			push_heap(pvet->begin(), pvet->end());
			PrintfVectorInt(*pvet);

			//删除数据  要先调用pop_heap()，再在容器中删除
			pop_heap(pvet->begin(), pvet->end());
			pvet->pop_back();
			pop_heap(pvet->begin(), pvet->end());
			pvet->pop_back();
			PrintfVectorInt(*pvet);

			//堆排序
			sort_heap(pvet->begin(), pvet->end());
			PrintfVectorInt(*pvet);

			delete pvet;
			return 0;
		}
	};
}

#if 1
int main()
{
	/*vector<pair<int, int>> req;
	req.push_back(make_pair(1, 0));
	req.push_back(make_pair(2, 0));
	req.push_back(make_pair(3, 1));
	req.push_back(make_pair(3, 2));

	panzg_leetcode::Solution sol;
	auto res = sol.findOrder(4, req);
	for each (auto var in res)
	{
		cout << var << endl;
	}*/


	vector<int> vec = { 3, 2, 1, 5, 6, 4 };
	panzg_leetcode::Solution sol;
	
	cout << sol.findKthLargest_v2(vec,3);
	getchar();
}
#endif