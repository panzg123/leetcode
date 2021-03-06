#include"header.h"
using namespace std;
namespace panzg_leetcode
{
	class Solution
	{
	public:
		class LIS
		{
		public:
			LIS(vector<int> _nums) :nums(_nums){}
			//获得最长递增子序列
			vector<int> get_lis()
			{
				vector<int> len_dp = get_length();
				vector<int> ret = solve_lis(len_dp);
				return ret;
			}
		private:
			vector<int> nums;
			//dp求解长度
			vector<int> get_length()
			{
				//状态转移方程为：dp[i]=max{dp[j]+1(0<=j<i,arr[j]<arr[i])}
				vector<int> ret(nums.size(), 1);
				for (int i = 0; i < nums.size(); i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (nums[j] < nums[i])
							ret[i] = max(ret[i], ret[j] + 1);
					}
				}
				return ret;
			}
			//从右向左获取最长递增子序列
			vector<int> solve_lis(vector<int> len_dp)
			{
				int len = 0;
				int index = 0;
				//先找到最大长度和索引
				for (int i = 0; i < len_dp.size(); i++)
				{
					if (len_dp[i] > len)
					{
						len = len_dp[i];
						index = i;
					}
				}
				//从右向左遍历
				vector<int> ret(len, 0);
				ret[--len] = nums[index];
				for (int i = index; i >= 0; i--)
				{
					if (nums[i] < nums[index] && len_dp[i] == len_dp[index] - 1)
					{
						ret[--len] = nums[i];
						index = i;
					}
				}
				return ret;
			}
		};
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
			for (int i = 0; i < nums.size(); i++)
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
			while (index > 1)
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
			int i = 0, j = s.length() - 1;
			while (i < j)
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
			if (index != s.length() - 1)
				str_res.assign(s, index + 1, string::npos);
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
			while (j < length - 1)
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
		int kmp_match(string src, int start_pos, string dest, const vector<int>& kmp_table)
		{
			int i = start_pos;
			int j = 0;
			int res = 0;
			while (i < src.length() && j < dest.length())
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
			vector<vector<int>> res(row + 1, vector<int>(col + 1, INT_MAX));
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
		//Contains Duplicate II,使用unordered_map<int,vector<int>>内存超出
		bool containsNearbyDuplicate(vector<int>& nums, int k)
		{
			int length = nums.size();
			if (length == 0 || k == 0)
				return false;
			//用vector<int>来记录nums[i]出现的位置索引
			unordered_map<int, vector<int>> map_index;
			for (int i = 0; i < nums.size(); i++)
			{
				auto find_res = map_index.find(nums[i]);
				if (find_res == map_index.end())
				{
					vector<int> temp_vec(i);
					map_index[nums[i]] = temp_vec;
				}
				else
					find_res->second.push_back(i);
			}
			for (auto iter = map_index.begin(); iter != map_index.end(); iter++)
			{
				if (iter->second.size() > 1)
				{
					auto vec = iter->second;
					for (int j = 1; j < vec.size(); j++)
					{
						if (vec[j] - vec[j - 1] <= k)
							return true;
					}
				}
			}
			return false;
		}
		//Contains Duplicate II,直接使用两层for循环超时
		bool containsNearbyDuplicate_v2(vector<int>& nums, int k)
		{
			int length = nums.size();
			if (length == 0 || k == 0)
				return false;
			for (int i = 0; i < length; i++)
			{
				for (int j = i + 1; j <= i + k; j++)
				{
					if (j < length && nums[i] == nums[j])
						return true;
					else if (j >= length)
						break;
				}
			}
			return false;
		}
		//Contains Duplicate II，使用滚动的unordered_map<int,int>,可ac
		bool containsNearbyDuplicate_v3(vector<int>& nums, int k)
		{
			int length = nums.size();
			if (length == 0 || k == 0)
				return false;
			unordered_map<int, int> map_record;
			for (int i = 0; i < length; i++)
			{
				auto find_res = map_record.find(nums[i]);
				if (find_res != map_record.end() && map_record[nums[i]] + k >= i)
					return true;
				else
					map_record[nums[i]] = i;
			}
			return false;
		}
		//Contains Duplicate III，直接使用sort排序
		bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
		{
			if (nums.size() < 2) return false;
			vector<pair<long, int>> v;
			for (int i = 0; i < nums.size(); i++)
			{
				v.push_back(pair<long, int>((long)nums[i], i));
			}
			//排序
			sort(v.begin(), v.end(), cmp);
			for (int i = 0; i < nums.size(); i++)
			{
				int j = i + 1;
				while (j < v.size())
				{
					if (v[j].first - v[i].first > t)  break;
					else if (abs(v[i].second - v[j].second) <= k)
					{
						return true;
					}
					else
						j++;
				}
			}
			return false;
		}

		static bool cmp(pair<long, int> a, pair<long, int> b)
		{
			return a.first < b.first;
		}
		//Contains Duplicate III,使用multimap排序，和上面的思想一样
		//reference：https://leetcode.com/discuss/60011/c-28ms-solution-using-multimap
		bool containsNearbyAlmostDuplicate_multimap(vector<int>& nums, int k, int t)
		{
			multimap<long, int> map;
			//插入multimap中排序
			for (int i = 0; i < nums.size(); i++)
			{
				map.insert(make_pair(nums[i], i));
			}
			auto p1 = map.begin();
			while (p1 != map.end())
			{
				auto p2 = p1;
				p2++;
				while (p2 != map.end() && p2->first - p1->first <= t)
				{
					if (abs(p1->second - p2->second) <= k)
						return true;
					p2++;
				}
				p1++;
			}
			return false;
		}
		//Rectangle Area,求两个矩形的全部覆盖面积
		int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
		{
			int x = get_union(A, C, E, G);
			int y = get_union(B, D, F, H);

			int area1 = abs((A - C)*(B - D));
			int area2 = abs((E - G)*(F - H));
			return area1 + area2 - x*y;
		}
		//求区间[x1,x2]与区间[x3,x4]之间的交集距离
		int get_union(int x1, int x2, int x3, int x4)
		{
			if (x1 <= x3 && x2 >= x4)
				return x4 - x3;
			else if (x1 <= x3 && x2 <= x4 && x2 <= x3)
				return 0;
			else if (x1 <= x3 && x2 <= x4 && x2 >= x3)
				return x2 - x3;
			else if (x1 >= x3 && x2 <= x4)
				return x2 - x1;
			else if (x1 >= x3 && x2 >= x4 && x1 >= x4)
				return 0;
			else
				return x4 - x1;
		}
		//Implement Stack using Queues
		class Stack {
		public:
			queue<int> q;
			queue<int> q_swap;

			// Push element x onto stack.
			void push(int x) {
				if (q.empty())
					q.push(x);
				else
				{
					while (!q.empty())
					{
						auto temp = q.front();
						q_swap.push(temp);
						q.pop();
					}
					q.push(x);
					while (!q_swap.empty())
					{
						auto tmp = q_swap.front();
						q.push(tmp);
						q_swap.pop();
					}
				}
			}

			// Removes the element on top of the stack.
			void pop() {
				q.pop();
			}

			// Get the top element.
			int top() {
				return q.front();
			}

			// Return whether the stack is empty.
			bool empty() {
				return q.empty();
			}
		};
		// Invert Binary Tree
		TreeNode* invertTree(TreeNode* root) 
		{
			if (root == nullptr)
				return nullptr;
			TreeNode *tmp = root->right;
			root->right = root->left;
			root->left = tmp;
			invertTree(root->left);
			invertTree(root->right);
			return root;
		}
		//221. Maximal Square
		int maximalSquare(vector<vector<char>>& matrix)
		{
			if (matrix.size() == 0) return 0;
			int maxSq = 0;
			int nRow = matrix.size();
			int nCol = matrix[0].size();
			vector<vector<int>> dp(nRow + 1, vector<int>(nCol + 1, 0));
			//dp[i][j] represents max square ending at position (i-1, j-1)
			for (int i = 1; i <= nRow; ++i)
			{
				for (int j = 1; j <= nCol; ++j)
				{
					if (matrix[i - 1][j - 1] == '1')
					{
						dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i][j - 1]) + 1;
						maxSq = max(maxSq, dp[i][j]);
					}
				}
			}
			return maxSq*maxSq;
		}

		//224. Basic Calculator
		//将所有括号展开，用sign_vec来记录符号变换，result记录计算结果
		int calculate(string s) 
		{
			vector<int> sign_vec = {1};
			int sign = 1;
			int num = 0;
			int result = 0;
			int length = s.length();
			for (int i = 0; i < length;i++)
			{
				if (s[i] == ' ')
				{
					continue;
				}
				else if (s[i] >= '0' && s[i] <= '9')
				{
					num = num * 10 + s[i] - '0';
					continue;
				}
				else if (s[i] == '(')
				{
					result += num*sign*sign_vec.back();
					sign_vec.push_back(sign*sign_vec.back());
					num = 0;
					sign = 1;

				}
				else if (s[i] == ')')
				{
					result += num*sign*sign_vec.back();
					num = 0;
					sign_vec.pop_back();
				}
				else if (s[i] == '+')
				{
					result += num*sign*sign_vec.back();
					sign = 1;
					num = 0;
				}
				else if (s[i] == '-')
				{
					result += num*sign*sign_vec.back();
					sign = -1;
					num = 0;
				}
			}
			result += num*sign*sign_vec.back();
			return result;
		}
		//直接先排序，后拷贝,时间复杂度O(N*logN)，空间复杂度O(N)
		void wiggleSort(vector<int>& nums) 
		{
			int length = nums.size();
			sort(nums.begin(), nums.end());
			copy(nums.cbegin(), nums.cend(), ostream_iterator<int>(cout, " "));
			cout << endl;
			vector<int> result(nums);
			int j = length - 1;
			for (int i = 1; i < length; i += 2, j--)
			{
				result[i] = nums[j];
			}
			for (int i = 0; i < length; i += 2, j--)
			{
				result[i] = nums[j];
			}
			nums = result;
		}
		//时间复杂度O(N)，空间复杂度O(1)，使用nth_element算法和three_way partition方法
		//参考 https://leetcode.com/discuss/77133/o-n-o-1-after-median-virtual-indexing
		//荷兰国旗问题请参考：http://www.cnblogs.com/gnuhpc/archive/2012/12/21/2828166.html
		void wiggleSort_v2(vector<int>& nums) 
		{
			int n = nums.size();

			// Find a median.
			auto midptr = nums.begin() + n / 2;
			nth_element(nums.begin(), midptr, nums.end());
			int mid = *midptr;

			// Index-rewiring.
			#define A(i) nums[(1+2*(i)) % (n|1)]

			// 3-way-partition-to-wiggly in O(n) time with O(1) space.
			int i = 0, j = 0, k = n - 1;
			while (j <= k) {
				if (A(j) > mid)
					swap(A(i++), A(j++));
				else if (A(j) < mid)
					swap(A(j), A(k--));
				else
					j++;
			}
		}
		//Summary Ranges,2ms
		vector<string> summaryRanges(vector<int>& nums)
		{
			vector<string> result;
			int begin = nums[0];
			int end = nums[0];
			if (nums.size() == 0)
				return result;
			if (nums.size() == 1)
			{
				result.push_back(to_string(begin));
				return result;
			}

			for (size_t i = 1; i < nums.size(); i++)
			{
				if (nums[i] == nums[i - 1] + 1)
					end++;
				else
				{
					if (begin != end)
						result.push_back(to_string(begin) + "->" + to_string(end));
					else
						result.push_back(to_string(begin));
					begin = nums[i];
					end = nums[i];
				}
			}
			if (begin != end)
				result.push_back(to_string(begin) + "->" + to_string(end));
			else
				result.push_back(to_string(begin));
			return result;
		}
		//Summary Ranges更快的方法，0ms
		vector<string> summaryRanges_v2(vector<int>& nums) 
		{
			const int size_n = nums.size();
			vector<string> res;
			if (0 == size_n) return res;
			for (int i = 0; i < size_n;) 
			{
				int start = i, end = i;
				while (end + 1 < size_n && nums[end + 1] == nums[end] + 1) 
					end++;
				if (end > start) 
					res.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
				else 
					res.push_back(to_string(nums[start]));
				i = end + 1;
			}
			return res;
		}
		//Power of Two，判断是否是2的幂
		bool isPowerOfTwo(int n)
		{
			/*
			 int result = 0;
			 unsigned int i, temp=1;
			 for(i=0; i<32; i++)
			{
				if((n & temp) == temp)
					result++;
				temp = temp << 1;
			}

			return result==1?true:false;
			*/
			return n > 0 && !(n&(n - 1));
		}
		//用log来计算，判断是否是3的幂
		bool isPowerOfThree(int n)
		{
			if(n<=0)
				return false;
			const double ratio = 1/log2(3);
			double diff = log2(n)*ratio;
			//如果是3的幂，则diff应该为整数
			return abs(diff-round(diff))<1e-13;
		}
		//循环除
		bool isPowerOfThree_v2(int n) 
		{
			if(n>1)
				while(n%3==0) n /= 3;
			return n==1;
		}
		// Basic Calculator II,用栈
		int calculate_2(string s)
		{
			stack<int> ele_stack;
			int length = s.length();
			char sign = '+';
			int num = 0;
			for (int i = 0; i < length;i++)
			{
				//计算数字
				if (isdigit(s[i]))
				{
					num = num * 10 + s[i] - '0';
				}
				//加减乘除
				if (!isdigit(s[i]) && !isspace(s[i]) || i == length - 1)
				{
					if (sign == '+')
						ele_stack.push(num);
					else if (sign == '-')
						ele_stack.push(-1 * num);
					else
					{
						int value;
						if (sign == '*')
							value = ele_stack.top()*num;
						else
							value = ele_stack.top() / num;
						ele_stack.pop();
						ele_stack.push(value);
					}
					sign = s[i];
					num = 0;
				}
			}
			//累加
			int result = num;
			while (!ele_stack.empty())
			{
				result += ele_stack.top();
				ele_stack.pop();
			}
			return result;
		}
		//Count Complete Tree Nodes，直接层次遍历，超时
		int countNodes(TreeNode* root) 
		{
			queue<TreeNode*> q;
			int count = 0;
			if (root != nullptr)
				q.push(root);
			else
				return 0;
			while (!q.empty())
			{
				if (q.front()->left != nullptr)
					q.push(q.front()->left);
				if (q.front()->right != nullptr)
					q.push(q.front()->right);
				count++;
				q.pop();
			}
			return count;
		}
		//递归方法，参考：https://leetcode.com/discuss/73892/a-very-clear-recursive-solution-isnt-it
		int countNodes_recursive(TreeNode* root)
		{
			if (root == nullptr)
				return 0;
			int left_height = countNodes_helper(root->left);
			int right_height = countNodes_helper(root->right);
			if (left_height == right_height)
				return (1 << left_height) + countNodes_recursive(root->right);
			else
				return (1 << right_height) + countNodes_recursive(root->left);
		}
		//计算树的深度
		int countNodes_helper(TreeNode* root)
		{
			if (root == nullptr)
				return 0;
			else
				return 1 + countNodes_helper(root->left);
		}
		//Expression Add Operators, https://leetcode.com/problems/expression-add-operators/
		//DFS遍历，经典操作
		vector<string> addOperators(string num, int target)
		{
			vector<string> res;
			if (num.empty()) return res;
			for (int i = 1; i <= num.size(); i++) 
			{
				string s = num.substr(0, i);
				long cur = stol(s);
				if (to_string(cur).size() != s.size()) 
					continue;
				addOperators_dfs(res, num, target, s, i, cur, cur, '#');// no operator defined.
			}

			return res;

		}
		//dfs遍历
		//result-->保存结果;cur-->目前的字符串；pos-->目前位置；cv-->目前值；pv-->前一个操作数；op-->上一个操作符
		void addOperators_dfs(vector<string>& result, const string& num, const int target, string cur,int pos, const long cv, const long pv, char op)
		{
			if (pos == num.size() && cv == target)
			{
				result.push_back(cur);
			}
			else
			{
				for (int i = pos + 1; i <= num.size(); i++)
				{
					string temp = num.substr(pos, i - pos);
					long value = stol(temp);
					if (to_string(value).size() != temp.size())
						continue;
					addOperators_dfs(result, num, target, cur + "+" + temp, i, cv + value, value, '+');
					addOperators_dfs(result, num, target, cur + "-" + temp, i, cv - value, value, '-');
					addOperators_dfs(result, num, target, cur + "*" + temp, i, (op == '-') ? cv + pv - pv*value : ((op == '+') ? cv - pv + pv*value : pv*value), pv*value, op);

				}
			}
		}
		//Kth Smallest Element in a BST,https://leetcode.com/problems/kth-smallest-element-in-a-bst/
		//直接递归，时间复杂度O(N)，空间复杂度O(N)
		int kthSmallest(TreeNode* root, int k) 
		{
			vector<int> result;
			kthSmallest_helper(root, result, k);
			if (result.size() == k)
				return result.back();
			else
				return 0;
		}
		void kthSmallest_helper(TreeNode *root, vector<int>& result,const int k)
		{
			if (root == nullptr)
				return;
			//中序遍历的思路
			kthSmallest_helper(root->left, result, k);
			if (result.size() == k)
				return;
			else
				result.push_back(root->val);
			kthSmallest_helper(root->right, result, k);
		}
		//不用递归，用栈，时间复杂度O(N)，空间复杂度O(N)
		int kthSmallest_v2(TreeNode* root, int k) 
		{
			TreeNode* current = NULL;
			stack<TreeNode*> s;
			current = root;
			int count = 1;
			while (1)
			{
				while (current)
				{
					s.push(current);
					current = current->left;
				}
				if (count == k)
				{
					TreeNode* node = s.top();
					return node->val;
				}
				if (count != k)
				{
					TreeNode* node = s.top();
					s.pop();
					current = node->right;
					count++;
				}
			}
		}
		//Implement Queue using Stacks,https://leetcode.com/problems/implement-queue-using-stacks/
		//用两个栈来实现队列
		class Queue 
		{
		private:
			stack<int> s1;
			stack<int> s2;
			void stack_move()
			{
				if (!s2.empty())
					return;
				while (!s1.empty())
				{
					int x = s1.top();
					s1.pop();
					s2.push(x);
				}
			}
		public:
			// Push element x to the back of queue.
			void push(int x)
			{
				s1.push(x);
			}

			// Removes the element from in front of queue.
			void pop(void)
			{
				if (s2.empty())
					stack_move();
				s2.pop();
			}

			// Get the front element.
			int peek(void)
			{
				if (s2.empty())
					stack_move();
				return s2.top();
			}

			// Return whether the queue is empty.
			bool empty(void)
			{
				return s1.empty() && s2.empty();
			}
		};
		int caculate_number1(int n)
		{
			int cur = 0;
			int low = 0;
			int factor = 1;
			int count = 0;
			while (n>=factor)
			{
				cur = (n / factor) % 10;
				low = n % factor;
				if (cur == 0)
					;
				else if (cur == 1)
					count += low + 1;
				else
					count += factor;
				factor *= 10;
			}
			return count;
		}
		//Number of Digit One,https://leetcode.com/problems/number-of-digit-one/
		//直接遍历，超时
		int countDigitOne(int n)
		{
			int count = 0;
			for (int i = 1; i <= n;i++)
			{
				int a = i;
				while (a)
				{
					if (a%10 == 1)
						count++;
					a /= 10;
				}
			}
			return count;
		}
		//数学题，找规律，《数学之美》，链接：http://www.cppblog.com/myjfm/archive/2012/09/04/189444.html
		int countDigitOne_v2(int n)
		{
			long high = 0;
			long low = 0;
			long cur = 0;
			long factor = 1;
			long count = 0;
			while (n>=factor)
			{
				high = n / (factor * 10);
				cur = (n / factor) % 10;
				low = n % factor;
				if (cur == 0)
					count += high*factor;
				else if (cur == 1)
					count += high*factor + 1 + low;
				else
					count += (high + 1)*factor;

				factor *= 10;
			}
			return count;
		}
		//Palindrome Linked List,https://leetcode.com/problems/palindrome-linked-list/
		//直接用栈可水过，但是空间复杂度为O(N)
		bool isPalindrome(ListNode* head)
		{
			stack<ListNode*> s;
			ListNode *cur = head;
			while (cur)
			{
				s.push(cur);
				cur = cur->next;
			}
			cur = head;
			while (cur)
			{
				if (cur->val != s.top()->val)
					return false;
				cur = cur->next;
				s.pop();
			}
			return true;
		}
		//Palindrome Linked List,首先找到链表的中间节点，将前半部分链表逆置，两个指针向后依次比较,空间复杂度为O(1)
		bool isPalindrome_v2(ListNode* head)
		{
			int count_length = 0;
			ListNode* cur = head;
			ListNode* reverse_head;
			int low_step = 0;
			//计算整个链表长度
			while (cur)
			{
				count_length++;
				cur = cur->next;
			}
			
			//获取后半部分的首指针
			cur = head;
			int i = 0;
			int len = (count_length % 2) == 0 ? count_length / 2 : count_length / 2 + 1;
			while (i< len)
			{
				i++;
				cur = cur->next;
			}

			//翻转长度为count_length/2的链表
			reverse_head = reverse_list_by_length(head, count_length/2);

			//前后两端比较
			while (cur!=nullptr && reverse_head != nullptr)
			{
				if(cur->val != reverse_head->val)
					return false;
				cur = cur->next;
				reverse_head = reverse_head->next;
			}
			return true;
		}

		//根据长度来翻转链表
		ListNode* reverse_list_by_length(ListNode* head, int length)
		{
			ListNode *pre = nullptr;
			ListNode *next = nullptr;
			int step = 0;
			while (step < length)
			{
				next = head->next;
				head->next = pre;
				pre = head;
				head = next;
				step++;
			}
			return pre;
		}
		// Lowest Common Ancestor of a Binary Search Tree,https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
		// 二叉查找树中的LCA问题，直接递归
		TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
		{
			if (p->val<root->val && q->val < root->val)
				return lowestCommonAncestor(root->left, p, q);
			if (p->val > root->val && q->val>root->val)
				return lowestCommonAncestor(root->right, p, q);
			return root;
		}
		//Lowest Common Ancestor of a Binary Tree,https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
		//二叉树中的LCA问题，递归解决
		TreeNode* lowestCommonAncestor_2(TreeNode* root, TreeNode* p, TreeNode* q)
		{
			if (!root || root == p || root == q)
				return root;
			TreeNode* left = lowestCommonAncestor_2(root->left, p, q);
			TreeNode* right = lowestCommonAncestor_2(root->right, p, q);
			//情况1：p&q节点都在root右子树
			if (left == nullptr)
				return right;
			else
			{
				//情况2：p和q都在root的左子树
				if (right == nullptr)
					return left;
				//情况3：p和q分别在root的左右子树
				else
					return root;
			}
		}
		//Add Digits,Digital Root问题，解法1如下：
		int addDigits(int num) 
		{
			int result=num;
			while(result>9)
			{
				int temp =0;
				while(result)
				{
					temp+=result%10;
					result/=10;
				}
            result=temp;
			}
        return result;
		}
		//解法2：reference:http://my.oschina.net/Tsybius2014/blog/497645
		int addDigits_v2(int num) 
		{
			return (num - 1) % 9 + 1;
		}
		//Product of Array Except Self,解法1，直接遍历，复杂度O(N*N)，超时
		vector<int> productExceptSelf(vector<int>& nums) 
		{
			vector<int> result(nums.size());
			for (size_t i = 0; i < nums.size(); i++)
			{
				result[i] = accumulate(nums.begin(), next(nums.begin(),i), 1,multiplies<int>())*
					accumulate(next(nums.begin(),i+1), nums.end(), 1, multiplies<int>());
			}
			return result;
		}
		//Product of Array Except Self,解法2，用两个数组来记录前后两端的乘积
		vector<int> productExceptSelf_v2(vector<int>& nums)
		{
			//记录前i个元素的乘积
			vector<int> from_begin_product(nums.size());
			//记录后i个元素的乘积
			vector<int> from_end_product(nums.size());
			from_begin_product[0] = 1;
			from_end_product[0] = 1;
			for (size_t i = 1; i < nums.size();i++)
			{
				from_begin_product[i] = from_begin_product[i-1] * nums[i - 1];
				from_end_product[i] = from_end_product[i-1] * nums[nums.size() - i];
			}
			vector<int> result(nums.size());
			for (size_t i = 0; i < nums.size();i++)
			{
				//result[i]等于前i个元素和后size-1-i个元素的乘积
				result[i] = from_begin_product[i] * from_end_product[nums.size()-1 - i];
			}
			return result;
		}
		//Sliding Window Maximum,https://leetcode.com/problems/sliding-window-maximum/
		//直接判断，时间复杂度为O(N*N)
		vector<int> maxSlidingWindow(vector<int>& nums, int k)
		{
			if (nums.size() == 0)
				return vector<int>();
			vector<int> result(nums.size() - k + 1);
			for (size_t i = 0; i < nums.size() - k + 1;i++)
			{
				result[i] = *max_element(next(nums.begin(), i), next(nums.begin(), i + k));
			}
			return result;
		}
		//deque很适用本场景,时间复杂度为O(N)
		vector<int> maxSlidingWindow_v2(vector<int>& nums, int k)
		{
			vector<int> ret;
			deque<int> max;
			for (int i = 0; i < nums.size(); ++i) 
			{
				//当当前值更大，则更新最大值
				while (!max.empty() && nums[i] > max.back()) 
				{
					max.pop_back();
				}
				max.push_back(nums[i]);
				//从第k个元素开始压入返回值
				if (i >= k - 1) 
				{
					ret.push_back(max.front());
					//如果当前窗口的最大值是该窗口的第一个值，则需要弹出
					if (nums[i - k + 1] == max.front()) 
					{
						max.pop_front();
					}
				}
			}
			return ret;
		}
		//Binary Tree Paths,https://leetcode.com/problems/binary-tree-paths/
		//求所有从根节点到叶子节点的路径，DFS问题
		vector<string> binaryTreePaths(TreeNode* root)
		{
			vector<string> ret;
			if (root == nullptr)
				return ret;
			binaryTreePaths_dfs(root,ret,"");
			return ret;
		}
		void binaryTreePaths_dfs(TreeNode* root,vector<string>& ret,string path)
		{
			if (root->left == nullptr && root->right == nullptr)
			{
				path += to_string(root->val);
				ret.push_back(path);
				return;
			}
			path += to_string(root->val);
			path += "->";
			if (root->left != nullptr)
				binaryTreePaths_dfs(root->left, ret, path);
			if (root->right != nullptr)
				binaryTreePaths_dfs(root->right, ret, path);
		}
		//Ugly Number II，https://leetcode.com/problems/ugly-number-ii/
		//直接查找第n个丑数，超时
		int nthUglyNumber(int n)
		{
			int start = 1;
			int ugly_idx = 0;
			while (ugly_idx < n)
			{
				if (isUgly(start++))
					ugly_idx++;
			}
			return start-1;
		}
		//用DP算法求解,
		int nthUglyNumber_dp(int n)
		{
			if (n == 1)
				return 1;
			vector<int> ret(n);
			ret[0] = 1;
			//指向2,3,5的索引
			int p2_idx = 0, p3_idx = 0, p5_idx = 0;
			for (int i = 1; i < n;i++)
			{
				ret[i] = min(ret[p2_idx] * 2, min(ret[p3_idx] * 3, ret[p5_idx] * 5));
				//索引前移
				if (ret[i] == ret[p2_idx] * 2)
					p2_idx++;
				if (ret[i] == ret[p3_idx] * 3)
					p3_idx++;
				if (ret[i] == ret[p5_idx] * 5)
					p5_idx++;
			}
			return ret[n - 1];
		}
		//Single Number III,https://leetcode.com/problems/single-number-iii/
		//位运算,先全部数异或运算，得到a^b；然后找a^b某位为1，其他为0的数，再遍历一遍数组，结束时的数就是a或b中的一个。
		//最后，将得到的数再与a^b异或就是另一个数；
		vector<int> singleNumber(vector<int>& nums)
		{
			vector<int> ret(2);
			int res1 = 0, res2 = 0;
			for (int i = 0; i < nums.size(); i++)
			{
				res1 ^= nums[i];
			}
			//temp只保留a^b中最右的1，其他置0
			int temp = res1&(~res1 + 1);
			for (int i = 0; i < nums.size();i++)
			{
				if ((nums[i] & temp) != 0)
					res2 ^= nums[i];
			}
			ret[0] = res2;
			ret[1] = res2^res1;
			return ret;
		}
		//Missing Number,https://leetcode.com/problems/missing-number/
		//直接先排序，时间复杂度为O(N*N)
		int missingNumber(vector<int>& nums)
		{
			if (nums.size() == 0)
				return 0;
			//排序
			sort(nums.begin(), nums.end());
			int start = 0;
			for (int i = 0; i < nums.size(); i++)
			{
				if (nums[i] != start)
					return start;
				start++;
			}
			return start;
		}
		//时间复杂度为O(N)，具体参考：《面试指南》P386，l表示目前出现的数的范围[0,l],r表示可能出现的最大数值
		int missingNumber_v2(vector<int>& nums)
		{
			int l = 0;
			int r = nums.size();
			while (l<r)
			{
				//正常出现
				if (nums[l] == l)
					l++;
				//重复出现[0,l]的某数;或直接超出最大值；或者重复出现[l,r]的某数,此时都应该缩小r
				else if (nums[l] <= l-1 || nums[l]>r-1 || nums[nums[l]] == nums[l])
					nums[l] = nums[--r];
				//出现[l+1,r]之间的数，只是顺序不正确，此时需要交换位置
				else
					swap(nums[l], nums[nums[l]]);
			}
			return l;
		}
		//返回Num的字符串形式，num<1000
		string helper(int num)
		{
			vector<string> less_ten=
			{ "", " One", " Two", " Three", " Four", " Five", " Six", " Seven", " Eight", " Nine" };
			vector<string> less_twenty =
			{ " Ten", " Eleven", " Twelve", " Thirteen", " Fourteen", " Fifteen", " Sixteen", " Seventeen", " Eighteen", " Nineteen" };
			vector<string> less_hundred =
			{ "", "", " Twenty", " Thirty", " Forty", " Fifty", " Sixty", " Seventy", " Eighty", " Ninety" };

			string s;

			if (num != 0)
			{
				//获取个十百位
				int hundred = num / 100;
				num %= 100;
				int tenth = num / 10;
				int single = num % 10;

				if (hundred) s = s + less_ten[hundred] + " Hundred";

				if (tenth)
				{
					if (tenth == 1)
					{	
						//10-19之间的特殊数字
						s += less_twenty[single];
						return s;
					}
					else  s += less_hundred[tenth];

				}
				if (single) s += less_ten[single];
			}
			return s;
		}
		//Integer to English Words,https://leetcode.com/problems/integer-to-english-words/
		//字符串处理，参考：https://leetcode.com/discuss/55254/c-solution-4ms
		string numberToWords(int num) 
		{
			if (num == 0)
				return "Zero";
			//第一个元素起到占位的作用
			vector<string> unit=
			{ "", " Thousand", " Million", " Billion" };
			int parts[4] = { 0 };
			for (int i = 0; i < 4; ++i)
			{
				parts[i] = num % 1000;
				num /= 1000;
			}
			string s;
			for (int i = 0; i < 4; ++i)
			{
				if (parts[i] == 0) continue;
				s = helper(parts[i]) + unit[i] + s;
			}
			//删除首部的空格符
			s.erase(s.begin());
			return s;
		}
		//First Bad Version,https://leetcode.com/problems/first-bad-version/
		//二分法
		int firstBadVersion(int n) 
		{
			int lower = 1, upper = n, mid;
			while (lower < upper) 
			{
				//用lower + (upper - lower) / 2，而不是(lower + upper) / 2
				mid = lower + (upper - lower) / 2;
				if (!isBadVersion(mid)) 
					lower = mid + 1;
				else upper = mid;
			}
			return lower;
		}
		//H-Index,https://leetcode.com/problems/h-index/
		//直接先排序,h_index计算方法参考：https://en.wikipedia.org/wiki/H-index
		int hIndex(vector<int>& citations) 
		{
			if (citations.empty())
				return 0;
			sort(citations.begin(), citations.end());
			int n = citations.size();
			int i = 0;
			while (i < n && citations[i] < (n - i)) 
				i++;
			return n - i;
		}
		//H-Index,https://leetcode.com/problems/h-index/
		//hashtable，时间复杂度为O(N)
		int hIndex_v2(vector<int>& citations) 
		{
			if (citations.empty())
				return 0;
			int n = citations.size();
			vector<int> hash(n + 1, 0);
			for (int i = 0; i < n; ++i)
			{
				if (citations[i] >= n)
					hash[n]++;
				else
					hash[citations[i]]++;
			}
			int paper = 0;
			for (int i = n; i >= 0; --i)
			{
				paper += hash[i];
				if (paper >= i)
					return i;
			}
		}
		//H-Index II,https://leetcode.com/problems/h-index-ii/
		//需要时间复杂度为O(logN),二分法
		int hIndex2(vector<int>& citations)
		{
			int low_idx = 0;
			int up_idx = citations.size() - 1;
			while (low_idx<up_idx)
			{
				int mid = low_idx + (up_idx - low_idx) / 2; 
				if (citations[mid] < (citations.size() - mid))
					low_idx = mid + 1;
				else
					up_idx = mid;
			}
			//citations[low_idx]用来处理全为0的特殊情况
			return min(citations[low_idx],static_cast<int>(citations.size())-low_idx);
		}
		//最小硬币问题，动态规划
		int minCoins(vector<int>& coins, int sum)
		{
			if (coins.size() == 0 || sum < 0)
				return -1;
			int length = coins.size();
			int max = INT_MAX;
			vector <vector<int>> dp(length, vector<int>(sum+1,0));
			for (int i = 1; i <= sum;i++)
			{
				dp[0][i] = INT_MAX;
				if (i - coins[0] >= 0 && dp[0][i - coins[0]] != INT_MAX)
					dp[0][i] = dp[0][i - coins[0]] + 1;
			}
			int left = 0;
			for (int i = 1; i < length;i++)
			{
				for (int j = 1; j <= sum;j++)
				{
					left = INT_MAX;
					if (j - coins[i] >= 0 && dp[i][j - coins[i] != INT_MAX])
						left = dp[i][j - coins[i]] + 1;
					dp[i][j] = min(left, dp[i - 1][j]);
				}
			}
			return dp[length - 1][sum] != INT_MAX ? dp[length - 1][sum] : -1;
		}
		//Perfect Squares,https://leetcode.com/problems/perfect-squares/
		//memory limit exceede
		int numSquares(int n)
		{
			if (n < 0)
				return 0;
			vector<int> num;
			for (int i = 1; i*i <= n; i++)
			{
				num.push_back(i*i);
			}
			return minCoins(num, n);
		}
		//980ms,beat 1.7%
		int numSquares_v2(int n)
		{
			vector<int> nums;
			vector<int> dp(n + 1, INT_MAX);
			for (int i = 1; i*i <= n; i++)
			{
				nums.push_back(i*i);
				dp[i*i] = 1;
			}

			for (int i = 1; i < n; i++)
				for (int j = 0; j < nums.size(); j++)
				{
					if (dp[i] != INT_MAX&&i + nums[j] <= n)
						dp[i + nums[j]] = min(dp[i + nums[j]], dp[i] + 1);
				}
			return dp[n] == INT_MAX ? n : dp[n];
		}
		//134ms,beat 0.7%,普通方法太耗时，尝试static dp,bfs,math等方法
		//更快的方法请参考：https://leetcode.com/discuss/58056/summary-of-different-solutions-bfs-static-and-mathematics
		int numSquares_v3(int n)
		{
			if (n < 0)
				return 0;
			vector<int> nums;
			vector<int> dp(n + 1, 0);
			for (int i = 1; i*i <= n; i++)
			{
				nums.push_back(i*i);
			}
			for (int j = 1; j <= n;j++)
			{
				if (j - nums[0] >= 0 && dp[j - nums[0]] != INT_MAX)
					dp[j] = dp[j - nums[0]] + 1;
			}
			int left = 0;
			for (int i = 1; i < nums.size();i++)
			{
				for (int j = 1; j <= n;j++)
				{
					left = INT_MAX;
					if (j - nums[i] >= 0 && dp[j - nums[i]] != INT_MAX)
						left = dp[j - nums[i]] + 1;
					dp[j] = min(left, dp[j]);
				}
			}
			return dp[n] != INT_MAX ? dp[n] : -1;
		}
		//Move Zeroes,https://leetcode.com/problems/move-zeroes/
		//用begin_idx记录非零位置，剩余的位置填充0
		void moveZeroes(vector<int>& nums)
		{
			int begin_idx = 0;
			for (int i = 0; i < nums.size();i++)
			{
				if (nums[i] != 0)
					nums[begin_idx++] = nums[i];
			}
			while (begin_idx < nums.size())
			{
				nums[begin_idx++] = 0;
			}
		}
		//Find the Duplicate Number,https://leetcode.com/problems/find-the-duplicate-number/
		//抽屉原理，整个数组中如果小于等于n/2的数的数量大于n/2，说明1到n/2这个区间是肯定有重复数字的
		//否则，在[n/2+1,n]的范围中存在重复数
		int findDuplicate(vector<int> nums) 
		{
			int min = 0, max = nums.size() - 1;
			while (min <= max)
			{
				// 找到中间那个数
				int mid = min + (max - min) / 2;
				int cnt = 0;
				// 计算总数组中有多少个数小于等于中间数
				for (int i = 0; i < nums.size(); i++)
				{
					if (nums[i] <= mid)
					{
						cnt++;
					}
				}
				// 如果小于等于中间数的数量大于中间数，说明前半部分必有重复
				if (cnt > mid)
				{
					max = mid - 1;
					// 否则后半部分必有重复
				}
				else 
				{
					min = mid + 1;
				}
			}
			return min;
		}
		//映射找环法,快慢指针的方法
		//https://leetcode.com/discuss/61514/understood-solution-space-without-modifying-explanation
		int findDuplicate_v2(vector<int> nums)
		{
			int slow = 0;
			int fast = 0;
			do 
			{
				slow = nums[slow];
				fast = nums[nums[fast]];
			} while (slow != fast);
			int find = 0;
			while (find != slow)
			{
				slow = nums[slow];
				find = nums[find];
			}
			return find;
		}
		//Word Pattern,https://leetcode.com/problems/word-pattern/
		//hashtable
		bool wordPattern(string pattern, string str) 
		{
			auto str_vec = split(str, " ");
			if (str_vec.size() != pattern.size())
				return false;
			unordered_map<char, string> m1;
			unordered_map<string, char> m2;
			//正向匹配
			for (int i = 0; i < pattern.size();i++)
			{
				auto find_ret = m1.find(pattern[i]);
				if (find_ret != m1.end())
				{
					if (m1[pattern[i]] != str_vec[i])
						return false;
				}
				else
					m1[pattern[i]] = str_vec[i];
			}
			//逆向匹配
			for (int i = 0; i < pattern.size();i++)
			{
				auto find_ret = m2.find(str_vec[i]);
				if (find_ret != m2.end())
				{
					if (m2[str_vec[i]] != pattern[i])
						return false;
				}
				else
					m2[str_vec[i]] = pattern[i];
			}
			return true;
		}
		//分割字符串
		vector<std::string> split(std::string str, std::string pattern)
		{
			std::string::size_type pos;
			std::vector<std::string> result;
			str += pattern;//扩展字符串以方便操作
			int size = str.size();
			for (int i = 0; i < size; i++)
			{
				pos = str.find(pattern, i);
				if (pos < size)
				{
					std::string s = str.substr(i, pos - i);
					result.push_back(s);
					i = pos + pattern.size() - 1;
				}
			}
			return result;
		}
		//Nim Game,https://leetcode.com/problems/nim-game/
		//组合博弈问题，请参考：http://wenku.baidu.com/view/42db0d8e83d049649b6658d3.html?from=search
		bool canWinNim(int n)
		{
			(n % 4 == 0) ? false : true;
		}
		//Find Median from Data Stream,https://leetcode.com/problems/find-median-from-data-stream/
		//时间复杂度为O(logN)
		//用两个堆, max heap 和 min heap. 维持两个堆的大小相等(min堆可以比max堆多一个)
		//如元素[1,2,3,4,5,6],则max-heap =[-4,-5,-6],min-heap=[3,2,1],所以median=3-(-4)/2=3.5
		//如元素[1,2,3,4,5],则max-heap =[-4,-5],min-heap=[3,2,1]，所以median = min-heap.top()=3
		class MedianFinder 
		{
			priority_queue<long> small, large;
		public:

			void addNum(int num) {
				small.push(num);
				large.push(-small.top());
				small.pop();
				if (small.size() < large.size()) {
					small.push(-large.top());
					large.pop();
				}
			}

			double findMedian() {
				return small.size() > large.size()
					? small.top()
					: (small.top() - large.top()) / 2.0;
			}
		};
		//Serialize and Deserialize Binary Tree
		//二叉树的序列化与反序列化，递归，先序遍历序列化，另外也可以采用层次遍历序列化
		class Codec 
		{
		public:
			//分割字符串
			vector<std::string> split(std::string str, std::string pattern)
			{
				std::string::size_type pos;
				std::vector<std::string> result;
				str += pattern;//扩展字符串以方便操作
				int size = str.size();
				for (int i = 0; i < size; i++)
				{
					pos = str.find(pattern, i);
					if (pos < size)
					{
						std::string s = str.substr(i, pos - i);
						result.push_back(s);
						i = pos + pattern.size() - 1;
					}
				}
				return result;
			}

			// Encodes a tree to a single string.
			string serialize(TreeNode* root) 
			{
				if (root == nullptr)
					return "#!";
				string ret = to_string(root->val) + "!";
				ret += serialize(root->left);
				ret += serialize(root->right);
				return ret;
			}

			// Decodes your encoded data to tree.
			TreeNode* deserialize(string data) 
			{
				vector<string> split_ret = split(data, "!");
				split_ret.pop_back();
				queue<string> q;
				for (int i = 0; i < split_ret.size();i++)
				{
					q.push(split_ret[i]);
				}
				return reconOrder(q);
			}
			TreeNode* reconOrder(queue<string> &q)
			{
				string value = q.front();
				q.pop();
				if (value == "#")
					return nullptr;
				TreeNode *root = new TreeNode(stoi(value));
				root->left = reconOrder(q);
				root->right = reconOrder(q);
				return root;
			}
		};
		//最长公共字串，经典DP问题
		string longestCommonSubstring(const string& str1, const string& str2)
		{
			size_t size1 = str1.size();
			size_t size2 = str2.size();
			if (size1 == 0 || size2 == 0) return 0;

			vector<vector<int> > dp(size1, vector<int>(size2, 0));

			// 初始化
			for (int i = 0; i < size1; ++i)
			{
				dp[i][0] = (str1[i] == str2[0] ? 1 : 0);
			}
			for (int j = 0; j < size2; ++j)
			{
				dp[0][j] = (str1[0] == str2[j] ? 1 : 0);
			}
			//dp
			for (int i = 1; i < size1; ++i)
			{
				for (int j = 1; j < size2; ++j)
				{
					if (str1[i] == str2[j])
					{
						dp[i][j] = dp[i - 1][j - 1] + 1;
					}
				}
			}
			//找字串,max为长度，end_ix表示字串结束位置
			int max = 0;
			int end_idx = 0;
			for (int i = 0; i < size1; ++i)
			{
				for (int j = 0; j < size2; ++j)
				{
					if (max < dp[i][j])
					{
						max = dp[i][j];
						end_idx = i;
					}
				}
			}
			//获取字串并返回
			return str1.substr(end_idx - max + 1, max);
		}
		//最长公共子序列,时间辅助度和空间辅助度都是O(M*N)
		string get_lcs_subsequece(string str1, string str2) 
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
			//获取子序列
			int m = str1.size()-1;
			int n = str2.size()-1;
			string res;
			int index = dp[m][n]-1;
			while (index >= 0) 
			{
				if (n > 0 && dp[m][n] == dp[m][n - 1]) 
				{
					n--;
				}
				else if (m > 0 && dp[m][n] == dp[m - 1][n]) 
				{
					m--;
				}
				else 
				{
					res.insert(res.begin(), str1[m]);
					index--;
					/*res[index--] = str1[m];*/
					m--;
					n--;
				}
			}
			return res;
		}

		//https://leetcode.com/problems/remove-duplicate-letters/
		string removeDuplicateLetters(string s) 
		{
			vector<int> cand(256, 0);
			vector<bool> visited(256, false);
			for (char c : s)
				cand[c]++;
			string result = "0";
			for (char c : s) 
			{
				cand[c]--;
				if (visited[c]) continue;
				while (c < result.back() && cand[result.back()]) 
				{
					visited[result.back()] = false;
					result.pop_back();
				}
				result += c;
				visited[c] = true;
			}
			return result.substr(1);
		}

		//https://leetcode.com/problems/additive-number/
		//解法，递归
		bool isAdditiveNumber(string num) 
		{
			for (int i = 1; i <= num.size() / 2; i++) 
			{
				for (int j = 1; j <= (num.size() - i) / 2; j++) 
				{
					if (i >= 2 && num[0] == '0' || j >= 2 && num[i] == '0' || num[i + j] == '0')
						continue;
					if (isAdditiveNumber_helper(stol(num.substr(0, i)), stol(num.substr(i, j)), num.substr(i + j)))
						return true;
				}
			}
			return false;
		}
		bool isAdditiveNumber_helper(long num1, long num2, string num)
		{
			if (num.size() > 1 && num[0] == '0') return false;
			long sum = num1 + num2, numI = stol(num);
			long len = static_cast<long>(log10(sum)) + 1;
			if (numI == sum) return true;
			if (numI < sum || sum != stol(num.substr(0, len))) return false;
			else return isAdditiveNumber_helper(num2, sum, num.substr(len));
		}
		//小明投票
		int toupiao(vector<int> vote)
		{
			int ret = 0;
			toupiao_helper(ret, vote);
			return ret;
		}
		void toupiao_helper(int& ret, vector<int> vote)
		{
			auto pos = max_element(next(vote.begin(), 1), vote.end());
			if (*pos > vote[0])
			{
				vote[0] += 1;
				*pos -= 1;
				ret += 1;
				toupiao_helper(ret, vote);
			}
			else if (*pos == vote[0])
			{
				ret += 1;
				return;
			}
			else
				return;
		}
		//https://leetcode.com/problems/longest-increasing-subsequence/
		//简单动态规划，复杂度O(N^2)
		int lengthOfLIS(vector<int>& nums)
		{
			if (nums.size() == 1 || nums.size() == 0)
				return nums.size();
			vector<int> dp(nums.size(), 1);
			for (int i = 1; i < nums.size();i++)
			{
				for (int j = 0; j < i;j++)
				{
					if (nums[i] > nums[j])
						dp[i] = max(dp[i], dp[j] + 1);
				}
			}
			return *max_element(dp.begin(), dp.end());
		}
		//Reverse String,https://leetcode.com/submissions/detail/60166915/
		string reverseString(string s)
		{
			if (s.size() == 0 || s.size() == 1)
				return s;
			else
			{
				reverse(s.begin(), s.end());
				return s;
			}
		}
		//是否是元音
		bool is_vowel(char c)
		{
			if (c != 'a' && c != 'e'&& c != 'i' && c != 'o' && c != 'u'&& c != 'A' && c != 'E'&& c != 'I' && c != 'O' && c != 'U')
				return false;
			else
				return true;
		}
		//Reverse Vowels of a String ,https://leetcode.com/problems/reverse-vowels-of-a-string/
		string reverseVowels(string s)
		{
			if (s.size() == 0 || s.size() == 1)
				return s;
			int i = 0, j = s.size() - 1;
			while (i<j)
			{
				while (!is_vowel(s[i]))
				{
					i++;
				}
				while (!is_vowel(s[j]))
				{
					j--;
				}
				if (i < j)
				{
					swap(s[i], s[j]);
					i++; j--;
				}
			}
			return s;
		}
		//Intersection of Two Arrays,unordered_set
		vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
		{
			unordered_set<int> m(nums1.begin(), nums1.end());
			vector<int> res;
			for (auto a : nums2)
				if (m.count(a)) {
					res.push_back(a);
					m.erase(a);
				}
			return res;
		}
		//先排序，然后遍历
		vector<int> intersection_v2(vector<int>& nums1, vector<int>& nums2)
		{
			vector<int> ret;
			sort(nums1.begin(), nums1.end());
			sort(nums2.begin(), nums2.end());
			size_t i = 0, j = 0;
			while (i< nums1.size() && j < nums2.size())
			{
				if (nums1[i] == nums2[j])
				{
					if (ret.empty() || nums1[i] != ret.back())
						ret.push_back(nums1[i]);
					j++;
					i++;
				}
				else if (nums1[i] > nums2[j])
				{
					j++;
				}
				else
					i++;
			}
			return ret;
		}
		//用压缩集合的思想
		vector<int> intersection_v3(vector<int>& nums1, vector<int>& nums2)
		{
			vector<int> ret;
			//TODO,http://blog.csdn.net/jie1991liu/article/details/13168255
			return ret;
		}
        //https://leetcode.com/problems/top-k-frequent-elements/
        class topKFrequent_Solutions{
            typedef pair<int,int> myPair;

            class comparePair {
            public:
                bool operator() (const myPair& lhs, const myPair& rhs) const
                {
                    return lhs.second < rhs.second;
                }
            };
            class Solution {
            public:
                vector<int> topKFrequent(vector<int>& nums, int k) {
                    unordered_map<int,int> counter;
                    vector<int> res ;
                    for (auto it: nums) {
                        counter[it]++;
                    }

                    priority_queue<myPair,vector<myPair>, comparePair> heap;

                    for (auto it = counter.begin(); it != counter.end(); it++) {
                        heap.push(make_pair(it->first,it->second));
                    }

                    for (int i = 0; i < k; i++) {
                        res.push_back((heap.top()).first);
                        heap.pop();
                    }
                    return res;
                }
            };
        };
		class topKFrequent_Solutions_v2{
			typedef pair<int,int> myPair;
			class cmp
			{
			public:
				bool operator()(const myPair& lhs, const myPair& rhs)
				{
					return lhs.second < rhs.second;
				}
			};
			class Solution
			{
			public:
				vector<int> topKFrequent(vector<int>& nums,int k)
				{
					unordered_map<int, int> counter;
					vector<int> ret;
					for each (auto var in nums)
					{
						counter[var]++;
					}
					priority_queue<myPair, vector<myPair>, cmp> heap;
					for each (auto var in counter)
					{
						heap.push(make_pair(var.first, var.second));
					}
					for (int i = 0; i < k;i++)
					{
						ret.push_back(heap.top().first);
						heap.pop();
					}
					return ret;
				}
			};
		};

		//https://leetcode.com/problems/integer-break/ , DP
		int integerBreak(int n)
		{
			vector<int> dp(n+1,1);
			for (int i = 2; i <= n;i++)
			{
				for (int j = 2; j < i; j++)
				{
					dp[i] = max(dp[i], max(dp[j], j)*max(dp[i - j], i - j));
				}
			}
			return dp[n];
		}
		//https://leetcode.com/problems/power-of-four/, 与isPowerOfThree思路一样
		bool isPowerOfFour(int num)
		{
			if (num < 0)
				return false;
			const double ratio = 1/log10(4);
			double diff = log10(num)*ratio;
			return abs(diff - round(diff)) < 1e-13;
		}
		int valueCountOne(int n)
		{
			int count = 0;
			while (n)
			{
				if (n & 1 == 1)
					count++;
				n >>= 1;
			}
			return count;
		}
		//https://leetcode.com/problems/counting-bits/
		vector<int> countBits(int num)
		{
			vector<int> ret;
			for (size_t i = 0; i <= num; i++)
			{
				int count_one = valueCountOne(i);
				ret.push_back(count_one);
			}
			return ret;
		}
		//explanation,https://leetcode.com/discuss/92796/four-lines-c-time-o-n-space-o-n
		//the i&(i-1) drop the lowest set bit 1
		vector<int> countBits_v2(int num)
		{
			vector<int> ret(num + 1, 0);
			for (size_t i = 1; i <= num;i++)
			{
				ret[i] = ret[i&(i - 1)] + 1;
			}
			return ret;
		}
		//https://leetcode.com/problems/house-robber-iii/
		unordered_map<TreeNode*, int> cache;
		int rob(TreeNode* root) {
			if (root == NULL) return 0;
			unordered_map<TreeNode*, int>::iterator it = cache.find(root);
			if (it != cache.end()) return it->second;
			int sum1 = root->val;//选择root节点
			int sum2 = 0; //不选择root节点
			if (root->left != NULL) {
				sum1 += rob(root->left->left) + rob(root->left->right);
				sum2 += rob(root->left);
			}
			if (root->right != NULL) {
				sum1 += rob(root->right->left) + rob(root->right->right);
				sum2 += rob(root->right);
			}
			int res = sum1 > sum2 ? sum1 : sum2;
			cache[root] = res;
			return res;
		}
		bool isPalindromeString(const string& str)
		{
			size_t index_low = 0;
			size_t index_high = str.size() - 1;
			while (index_low < index_high)
			{
				if (str[index_low] != str[index_high])
					return false;
				index_low++;
				index_high--;
			}
			return true;
		}
		//https://leetcode.com/problems/palindrome-pairs/
		//暴力法,O(N^2*K)，超时
		vector<vector<int>> palindromePairs(vector<string>& words)
		{
			vector<vector<int>> ret;
			for (size_t i = 0; i < words.size();i++)
			{
				for (size_t j = 0; j < words.size();j++)
				{
					if (i != j)
					{
						string temp = words[i] + words[j];
						bool is_huiwen = isPalindromeString(temp);
						if (is_huiwen)
						{
							vector<int> temp;
							temp.push_back(i);
							temp.push_back(j);
							ret.push_back(temp);
						}
					}
				}
			}
			return ret;
		}
		//https://leetcode.com/problems/palindrome-pairs/
		//用unordered_map,平均时间复杂度O(N*K^2),其中N是word列表的元素个数，k是单词的平均长度
		class palindromePairs_Solution
		{
		public:
			vector<vector<int>> palindromePairs(vector<string>& words) 
			{
				unordered_map<string, int> dict;
				vector<vector<int>> ans;
				// build dictionary
				for (int i = 0; i < words.size(); i++) 
				{
					string key = words[i];
					reverse(key.begin(), key.end());
					dict[key] = i;
				}
				// edge case: if empty string "" exists, find all palindromes to become pairs ("", self)
				if (dict.find("") != dict.end())
				{
					for (int i = 0; i < words.size(); i++)
					{
						if (i == dict[""]) 
							continue;
						if (isPalindrome(words[i])) 
							ans.push_back({ dict[""], i }); // 1) if self is palindrome, here ans covers concatenate("", self) 
					}
				}

				for (int i = 0; i < words.size(); i++) 
				{
					for (int j = 0; j < words[i].size(); j++) 
					{
						string left = words[i].substr(0, j);
						string right = words[i].substr(j, words[i].size() - j);

						if (dict.find(left) != dict.end() && isPalindrome(right) && dict[left] != i) 
						{
							ans.push_back({ i, dict[left] });    //left | right | candidate
						}

						if (dict.find(right) != dict.end() && isPalindrome(left) && dict[right] != i) 
						{
							ans.push_back({ dict[right], i });  // candidate | left | right.
						}
					}
				}

				return ans;
			}

			bool isPalindrome(string str)
			{
				int i = 0;
				int j = str.size() - 1;

				while (i < j) 
				{
					if (str[i++] != str[j--]) 
						return false;
				}

				return true;
			}

		};
		//https://leetcode.com/problems/increasing-triplet-subsequence/
		//直接DP时间复杂度和空间复杂度很高
		bool increasingTriplet(vector<int>& nums)
		{
			//状态转移方程为：dp[i]=max{dp[j]+1(0<=j<i,arr[j]<arr[i])}
			vector<int> ret(nums.size(), 1);
			for (int i = 0; i < nums.size(); i++)
			{
				for (int j = 0; j < i; j++)
				{
					if (nums[j] < nums[i])
					{
						ret[i] = max(ret[i], ret[j] + 1);
						if (ret[i] == 3)
							return true;
					}
				}
			}
			return false;
		}
		//时间复杂度O(N)，空间复杂度O(1)
		bool increasingTriplet_v2(vector<int>& nums)
		{
			int c1 = INT_MAX, c2 = INT_MAX;
			for (int x : nums) 
			{
				if (x <= c1) 
				{
					c1 = x;           // c1 is min seen so far (it's a candidate for 1st element)
				}
				else if (x <= c2)
				{					  // here when x > c1, i.e. x might be either c2 or c3
					c2 = x;           // x is better than the current c2, store it
				}
				else 
				{                     // here when we have/had c1 < c2 already and x > c2
					return true;      // the increasing subsequence of 3 elements exists
				}
			}
			return false;
		}
		//https://leetcode.com/problems/self-crossing/
		//数学题，讲解见https://leetcode.com/discuss/89336/best-submission-searching-for-the-crossing-patterns-the-key
		//以下三种情况会相交：(1)第i条线，相交于第i-3条线；(2)第i条线，相交于i-4条线，即两线重合；(3)第i条线，相交于第i-5条线
		bool isSelfCrossing(vector<int>& x)
		{
			size_t size = x.size();
			for (int i = 3; i < size; i++)
			{
				if (x[i] >= x[i - 2] && x[i - 1] <= x[i - 3]) return true;
				if (i >= 4 && x[i - 1] == x[i - 3] && x[i] + x[i - 4] >= x[i - 2]) return true;
				if (i >= 5 && x[i - 2] - x[i - 4] >= 0 && x[i] >= x[i - 2] - x[i - 4] && x[i - 1] >= x[i - 3] - x[i - 5] && x[i - 1] <= x[i - 3]) return true;
			}
			return false;
		}
		//https://leetcode.com/problems/reconstruct-itinerary/
		//explanation:https://leetcode.com/discuss/84659/short-ruby-python-java-c
		class findItineraryClass
		{
		public:
			vector<string> findItinerary(vector<pair<string, string>> tickets) {
				for (auto ticket : tickets)
					targets[ticket.first].insert(ticket.second);
				visit("JFK");
				return vector<string>(route.rbegin(), route.rend());
			}

			map<string, multiset<string>> targets;
			vector<string> route;

			void visit(string airport) {
				while (targets[airport].size()) {
					string next = *targets[airport].begin();
					targets[airport].erase(targets[airport].begin());
					visit(next);
				}
				route.push_back(airport);
			}
		};
		//二叉树性质，n个树节点，则n+1空节点，先序遍历的最后一个节点为空节点
		class isValidSerializationSolution 
		{
		public:
			bool isValidSerialization(string preorder) 
			{
				istringstream s(preorder);
				int node_c = 0, null_c = 0;
				string cur;
				while (getline(s, cur, ',')) 
				{
					if (cur == "#") 
						++null_c;
					else
						++node_c;
					if (s.good() && null_c == node_c + 1) 
						return false;
				}
				return null_c == node_c + 1;
			}
		};

		//nums代表每步能调的距离，求跳到最右的最小步数
		//简单动态规划
		int minSteps(vector<int> nums)
		{
			int length = nums.size();
			vector<int> dp(length, length-1);
			dp[0] = 0;    
			for (int i = 0; i < length;i++)
			{
				int step = nums[i];
				for (int j = 1; j <= step && (j + i) < length;j++)
				{
					dp[j + i] = min(dp[j + i], dp[i] + 1);
				}
			}
			return dp[length - 1];
		}
		//给定一颗二叉树，求此二叉树的最大距离，题目见《程序员代码面试指南》p169,时间复杂度O(N)
		int maxDistance(TreeNode* root)
		{
			auto ret = maxDistance_helper(root);
			return ret.first;
		}
		//一个后续遍历的过程
		pair<int,int> maxDistance_helper(TreeNode* root)
		{
			if(root == nullptr)
				return make_pair(0,0);
			auto left = maxDistance_helper(root->left);
			auto right = maxDistance_helper(root->right);
			pair<int, int> ret;//first成员记录最远距离，second成员记录距离root节点的最大距离
			ret.first = max(max(left.first, right.first),left.second+right.second+1);
			ret.second = max(left.second, right.second) + 1;
			return ret;
		}
		//计算一个完全二叉树的节点数目
		int nodeNum(TreeNode* root)
		{
			if (root == nullptr)
				return 0;
			return nodeNum_helper(root,1,mostLeftLevel(root,1));
		}
		int nodeNum_helper(TreeNode* root,int cur_level,int high)
		{
			if (cur_level == high)
				return 1;
			if (mostLeftLevel(root->right, cur_level + 1) == high) //左子树满二叉树
				return (1 << (high - cur_level)) + nodeNum_helper(root->right, cur_level + 1, high);
			else //右子树满二叉树
				return (1 << (high - cur_level - 1)) + nodeNum_helper(root->left, cur_level + 1, high);
		}
		//计算当前root节点所在的level
		int mostLeftLevel(TreeNode* root, int level)
		{
			while (root != nullptr)
			{
				level++;
				root = root->left;
			}
			return level - 1;
		}
		//https://leetcode.com/problems/patching-array/?sort=votes
		//reference,https://leetcode.com/discuss/102653/c-8ms-greedy-solution-with-explanation
		int minPatches(vector<int>& nums, int n) 
		{
			int cnt = 0, i = 0;
			long long maxNum = 0;
			while (maxNum < n)
			{
				if (i < nums.size() && nums[i] <= maxNum + 1)
					maxNum += nums[i++];
				else
				{
					maxNum += maxNum + 1; cnt++;
				}
			}
			return cnt;
		}
		//https://leetcode.com/problems/coin-change/
		//换钱的最小货币数目,动态规划，时间复杂度和空间复杂度均为O(N*amount)
		//此处，空间复杂度可以优化为O（amount）
		int coinChange(vector<int>& coins, int amount) 
		{
			sort(coins.begin(), coins.end());
			vector<vector<int>> dp(coins.size(), vector<int>(amount+1,INT_MAX));
			for (int i = 0; i <= amount; i++)
			{
				if (i % coins[0])
					dp[0][i] = INT_MAX;
				else
					dp[0][i] = i / coins[0];
			}
			for (int i = 1; i < coins.size(); i++)
				dp[i][0] = 0;
			for (int i = 1; i < coins.size(); i++)
			{
				for (int j = 1; j <= amount; j++)
				{
					int left = INT_MAX;
					if (j - coins[i] >= 0 && dp[i][j - coins[i]]!=INT_MAX)
						left = dp[i][j - coins[i]] + 1;
					dp[i][j] = min(left, dp[i - 1][j]);
				}
			}
			return dp[coins.size() - 1][amount] == INT_MAX ? -1 : dp[coins.size() - 1][amount];
		}
		//时间复杂度O(N*amount),空间复杂度O(amount)
		int coinChange_v2(vector<int>& coins, int amount)
		{
			sort(coins.begin(), coins.end());
			vector<int> dp(amount+1, 0);
			for (int i = 1; i <= amount;i++)
			{
				if (i%coins[0])
					dp[i] = INT_MAX;
				else
					dp[i] = i / coins[0];
			}
			for (int i = 1; i < coins.size();i++)
			{
				for (int j = 1; j <= amount;j++)
				{
					int left = INT_MAX;
					if (j - coins[i] >= 0 && dp[j - coins[i]] != INT_MAX)
						left = dp[j - coins[i]] + 1;
					dp[j] = min(dp[j], left);
				}
			}
			return dp[amount] == INT_MAX ? -1 : dp[amount];
		}
		//https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
		//暴力DFS，超时,可以对长度进行存储，见longestIncreasingPath_dp
		int longestIncreasingPath(vector<vector<int>>& matrix) 
		{
			int ret = 0;
			for (int i = 0; i < matrix.size();i++)
			{
				for (int j = 0; j < matrix.size();j++)
				{
					ret = max(ret, longestIncreasingPath_helper(matrix, 1, i, j));
				}
			}
			return ret;
		}
		int longestIncreasingPath_helper(vector<vector<int>>& matrix,int cur_length,int cur_x,int cur_y)
		{
			int ret = cur_length;
			if (cur_x > 0 && matrix[cur_x - 1][cur_y] > matrix[cur_x][cur_y])
				ret = max(ret, longestIncreasingPath_helper(matrix, cur_length + 1, cur_x - 1, cur_y));
			if (cur_y < matrix[0].size()-1 && matrix[cur_x][cur_y+1] > matrix[cur_x][cur_y])
				ret = max(ret, longestIncreasingPath_helper(matrix, cur_length + 1, cur_x, cur_y + 1));
			if (cur_x < matrix.size()-1 && matrix[cur_x + 1][cur_y] > matrix[cur_x][cur_y])
				ret = max(ret, longestIncreasingPath_helper(matrix, cur_length + 1, cur_x + 1, cur_y));
			if (cur_y > 0 && matrix[cur_x][cur_y - 1] > matrix[cur_x][cur_y])
				ret = max(ret, longestIncreasingPath_helper(matrix, cur_length + 1, cur_x, cur_y - 1));
			return ret;
		}
		//dfs+dp,400ms
		int longestIncreasingPath_dp(vector<vector<int>>& matrix)
		{
			int rows = matrix.size();
			if (!rows) return 0;
			int cols = matrix[0].size();

			//dp[x][y]表示以(x,y)为起点的最大长度
			vector<vector<int>> dp(rows, vector<int>(cols, 0));
			std::function<int(int, int)> dfs = [&](int x, int y) 
			{
				if (dp[x][y]) 
					return dp[x][y];
				vector<vector<int>> dirs = { { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };
				for (auto &dir : dirs) //遍历四个方向，找到最大值
				{
					int xx = x + dir[0], yy = y + dir[1];
					if (xx < 0 || xx >= rows || yy < 0 || yy >= cols) 
						continue;
					if (matrix[xx][yy] <= matrix[x][y]) 
						continue;
					dp[x][y] = std::max(dp[x][y], dfs(xx, yy));
				}
				//+1
				return ++dp[x][y];
			};

			int ret = 0;
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					ret = std::max(ret, dfs(i, j));
				}
			}
			return ret;
		}
		//同样DFS+DP，但只需60ms，优化在function函数对象
		class longestIncreasingPathSolution {
			vector<vector<int>> visited;
			int height = 0, width = 0;
			int floodfill(vector<vector<int>>& matrix, int cur, int i, int j)
			{
				if (i < 0 || i >= height || j < 0 || j >= width)
					return 0;
				if (matrix[i][j] <= cur)
					return 0;
				if (visited[i][j] > 0)
					return visited[i][j];
				int r = floodfill(matrix, matrix[i][j], i + 1, j);
				int l = floodfill(matrix, matrix[i][j], i - 1, j);
				int u = floodfill(matrix, matrix[i][j], i, j + 1);
				int d = floodfill(matrix, matrix[i][j], i, j - 1);
				visited[i][j] = max(r, max(l, max(u, d))) + 1;
				return visited[i][j];
			}
		public:
			int longestIncreasingPath(vector<vector<int>>& matrix) {
				if (matrix.empty())
					return 0;
				height = matrix.size(), width = matrix[0].size();
				visited.resize(height, vector<int>(width));
				int max_len = 0;
				for (int i = 0; i < height; ++i)
					for (int j = 0; j < width; ++j)
						max_len = max(max_len, floodfill(matrix, INT_MIN, i, j));
				return max_len;
			}
		};
		//Count of Range Sum, https://leetcode.com/problems/count-of-range-sum/
		//直接暴力遍历，超时
		int countRangeSum(vector<int>& nums, int lower, int upper) 
		{
			int ret = 0;
			vector<long long> sum(nums.size()+1, 0);
			sum[0] = nums[0];
			for (int i = 1; i <= nums.size();i++)
			{
				sum[i] = sum[i - 1] + nums[i-1];
			}
			for (int i = 0; i < nums.size();i++)
			{
				for (int j = i+1; j <= nums.size();j++)
				{
					if (sum[j] - sum[i] <= upper && sum[j] - sum[i] >= lower)
						ret += 1;
				}
			}
			return ret;
		}
		//Count of Smaller Numbers After Self,https://leetcode.com/problems/count-of-smaller-numbers-after-self/
		//MergeSort方法，暂时不理解
		class countSmallerSolution {
		protected:
			void merge_countSmaller(vector<int>& indices, int first, int last,vector<int>& results, vector<int>& nums) {
				int count = last - first;
				if (count > 1) {
					int step = count / 2;
					int mid = first + step;
					merge_countSmaller(indices, first, mid, results, nums);
					merge_countSmaller(indices, mid, last, results, nums);
					vector<int> tmp;
					tmp.reserve(count);
					int idx1 = first;
					int idx2 = mid;
					int semicount = 0;
					while ((idx1 < mid) || (idx2 < last)) {
						if ((idx2 == last) || ((idx1 < mid) &&
							(nums[indices[idx1]] <= nums[indices[idx2]]))) {
							tmp.push_back(indices[idx1]);
							results[indices[idx1]] += semicount;
							++idx1;
						}
						else {
							tmp.push_back(indices[idx2]);
							++semicount;
							++idx2;
						}
					}
					move(tmp.begin(), tmp.end(), indices.begin() + first);
				}
			}
		public:
			vector<int> countSmaller(vector<int>& nums) {
				int n = nums.size();
				vector<int> results(n, 0);
				vector<int> indices(n, 0);
				iota(indices.begin(), indices.end(), 0);
				merge_countSmaller(indices, 0, n, results, nums);
				return results;
			}
		};
		//Count of Smaller Numbers After Self, https://leetcode.com/problems/count-of-smaller-numbers-after-self/
		//BST方法
		class countSmallerSolutionBST {
		public:
			vector<int> countSmaller(vector<int>& nums) 
			{
				vector<int> clone = nums;;
				int len = (int)nums.size();
				unordered_map<int, int> reflect;
				array.resize(len + 1);
				sort(clone.begin(), clone.end());
				for (int i = 0; i < len; ++i)
					reflect[clone[i]] = i + 1;

				for (int i = len - 1; i >= 0; --i) 
				{
					clone[i] = query(reflect[nums[i]] - 1);
					add(reflect[nums[i]], 1);
				}
				return clone;
			}

		private:
			vector<int> array;
			inline int lowbit(int pos) 
			{
				return pos & -pos;
			}
			void add(int pos, int val) 
			{
				long len = array.size();
				while (pos < len) 
				{
					array[pos] += val;
					pos += lowbit(pos);
				}
			}
			int query(int pos) 
			{
				int ret = 0;
				while (pos > 0) 
				{
					ret += array[pos];
					pos -= lowbit(pos);
				}
				return ret;
			}
		};
		//https://leetcode.com/problems/odd-even-linked-list/
		ListNode* oddEvenList(ListNode* head)
		{
			if (head == nullptr)
				return head;
			ListNode* insert_pos = head;
			ListNode* del_pos = head->next;
			while (del_pos && del_pos->next)
			{
				ListNode *temp_del = del_pos->next->next;
				//delete the node
				ListNode *node_del = del_pos->next;
				del_pos->next = del_pos->next->next;
				//insert
				node_del->next = insert_pos->next;
				insert_pos->next = node_del;
				//update the pos
				insert_pos = insert_pos->next;
				del_pos = temp_del;
			}
			return head;

		}
	};
}

#if 0
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

	vector<vector<char>> vec1 = {
		{ '0', '0', '0', '1' },
		{ '1', '1', '0', '1' },
		{ '1', '1', '1', '1' },
		{ '0', '1', '1', '1' },
		{ '0', '1', '1', '1' }
	};

	vector<vector<int>> matrix = {
		{ 3, 4, 5 },
		{ 3, 2, 6 },
		{ 2, 2, 1 }
	};
	//panzg_leetcode::Solution sol;

	TreeNode node1(1);
	TreeNode node2(2);
	TreeNode node3(3);
	TreeNode node4(4);
	TreeNode node5(5);
	TreeNode node6(6);
	TreeNode node7(7);
	node1.left = &node2;
	node1.right = &node3;
	node2.left = &node4;
	node2.right = &node5;
	node3.left = &node6;
	node3.right = &node7;
	

	//panzg_leetcode::Solution::Codec code;
	//auto ret = code.deserialize(code.serialize(&node1));

	//cout << sol.isAdditiveNumber("112358");

	//vector<int> nums1 = { 1, 2, 2, 1 };
	//vector<int> nums2 = { 2, 2 };
	//auto ret = sol.countBits_v2(5);
	//for each (auto var in ret)
	//{
	//	cout << var << " ";
	//}

	panzg_leetcode::Solution sol;
	vector<pair<string, string>> data;
	data.push_back(make_pair("JFK", "SFO"));
	data.push_back(make_pair("JFK", "ATL"));
	data.push_back(make_pair("SFO", "ATL"));
	data.push_back(make_pair("ATL", "JFK"));
	data.push_back(make_pair("ATL", "SFO"));



	vector<int> nums = { 3, 2, 3, 1, 1, 4 };
	auto ret = sol.nodeNum(&node1);
	
	std::cout << ret << std::endl;
	
	system("pause");
	return 0;

}
#endif