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
			vector<int> in_degree(numCourses, 0); //�洢���
			vector<unordered_set<int>> matrix(numCourses);//�洢ͼ
			vector<int> res;

			for (int i = 0; i < prerequisites.size(); i++)
			{
				matrix[prerequisites[i].second].insert(prerequisites[i].first);
			}
			//�������
			for (int i = 0; i < numCourses; i++)
			{
				for (auto it = matrix[i].begin(); it != matrix[i].end(); it++)
				{
					in_degree[*it]++;
				}
			}
			stack<int> zeor_degree_stack;//�洢���Ϊ0�Ľڵ�
			int count = 0;//���0�Ľڵ������
			for (int i = 0; i < numCourses; i++)
			{
				if (in_degree[i] == 0)
				{
					zeor_degree_stack.push(i);
					count++; //���Ϊ0��������1
					res.push_back(i);
				}
			}
			//ѭ����ȡ���Ϊ0�Ľڵ�
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
		/*Different Ways to Add Parentheses,�ݹ�*/
		vector<int> diffWaysToCompute(string input)
		{
			int length = input.size();
			vector<int> res;
			for (int i = 0; i < length; i++)
			{
				char c = input[i];
				//������
				if (ispunct(c))
				{
					vector<int> l_res = diffWaysToCompute(input.substr(0, i)); //��˽��
					vector<int> r_res = diffWaysToCompute(input.substr(i + 1)); //�Ҷ˽��
					//���
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
			//�ַ���ת��Ϊ����
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
		//Shortest Palindrome,ֱ��ѭ���жϣ���ʱ
		string shortestPalindrome(string s)
		{
			string temp;
			int index = s.length();
			//���ַ���ĩβ���ң���Ļ��Ĵ�
			while (index > 1)
			{
				temp.assign(s, 0, index);
				if (is_palindrome(temp))
					break;
				else
					index--;
			}
			//�ҵ�����Ĵ���������
			if (index != s.length())
				temp.assign(s, index, string::npos);
			else
				return s;
			reverse(temp.begin(), temp.end());
			temp += s;
			return temp;
		}
		//�ж��Ƿ����
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
		//Shortest Palindrome,kmpƥ�䷨��������Բο����⣺https://leetcode.com/discuss/64309/clean-kmp-solution-with-super-detailed-explanation
		string shortestPalindrome_kmp(string s)
		{
			//�ȹ����ַ���:s+"#"+reverse(s),����catacb�Ĺ�����Ϊ��catacb # bcatac�����浽temp
			string temp = s;
			string str_res;
			temp += "#";
			string temp2 = s;
			reverse(temp2.begin(), temp2.end());
			temp += temp2;
			//��ȡkmp��
			vector<int> res(temp.size(), 0);
			kmp_get_next(temp, res);
			//ȡ����kmpĩβ��ֵ
			int index = res[temp.size() - 1];
			if (index != s.length() - 1)
				str_res.assign(s, index + 1, string::npos);
			else
				return s;
			reverse(str_res.begin(), str_res.end());
			//�洢���
			str_res += s;
			return str_res;
		}
		//kmp table��ʱ�临�Ӷ�ΪO(N)�����ؽ���洢��next��
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
		//������kmpƥ�䣬ʱ�临�Ӷ�ΪO(N+M)
		//@src������
		//@start_pos:����ƥ����ʼλ��
		//@dest:ģʽ��
		//@kmp_table:kmp����kmp_get_next�������
		//@return:��������ƥ���λ�ã���ƥ���򷵻�-1
		int kmp_match(string src, int start_pos, string dest, const vector<int>& kmp_table)
		{
			int i = start_pos;
			int j = 0;
			int res = 0;
			while (i < src.length() && j < dest.length())
			{
				if (j == -1 || src[i] == dest[j]) //�ֱ�����1
				{
					i++;
					j++;
				}
				else
					j = kmp_table[j]; //ģʽ������
			}
			if (j == dest.length())
				res = i - dest.length();
			else
				res = -1;
			return res;
		}
		//Ugly Number,�ݹ�
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
		//˼·����unordered_map����¼���ֵ���������ظ����֣�����ѭ��
		string fractionToDecimal(int numerator, int denominator)
		{
			string result;
			if (numerator == 0)
				return "0";
			if (denominator == 0)
				return "";
			//���
			if ((numerator < 0) ^ (denominator < 0))
				result += "-";
			long long a = abs((long long)numerator);
			long long b = abs((long long)denominator);
			//�����������
			result += to_string(abs(a) / abs(b));
			if (numerator%denominator == 0)
				return result;
			result += ".";
			//��С������
			unordered_map<int, int> map;
			for (long long r = a%b; r; r %= b)
			{
				if (map.count(r) > 0)
				{
					//����rλ�õ�ǰ�����'('
					result.insert(map[r], 1, '(');
					result += ")";
					break;
				}
				//������r���ֵ�λ��
				map[r] = result.size();
				r *= 10;
				result += to_string(r / b);
			}
			return result;
		}
		//Dungeon Game,��̬�滮���ص��Ǵ����½ǿ�ʼѭ��
		int calculateMinimumHP(vector<vector<int>> &dungeon)
		{
			int row = dungeon.size();
			int col = dungeon[0].size();
			//res��¼�ڵ�res[i][j]����Ҫ������hp
			vector<vector<int>> res(row + 1, vector<int>(col + 1, INT_MAX));
			res[row - 1][col] = 1;
			res[row][col - 1] = 1;
			for (int i = row - 1; i >= 0; --i)
			{
				for (int j = col - 1; j >= 0; --j)
				{
					//ѡ���ұ߻����±��н�С��hpֵ
					int t = min(res[i + 1][j], res[i][j + 1]) - dungeon[i][j];
					//��СΪ1
					res[i][j] = max(t, 1);
				}
			}
			//�������϶�����Ҫ��hpֵ
			return res[0][0];
		}
		//Kth Largest Element in an Array ,ֱ��������,12ms
		int findKthLargest(vector<int>& nums, int k)
		{
			sort(nums.begin(), nums.end());
			return nums[nums.size() - k];
		}
		//Kth Largest Element in an Array ,��,28ms,����������ο���https://leetcode.com/discuss/36966/solution-explained
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

			//��̬����vector ����vector����
			vector<int> *pvet = new vector<int>(40);
			pvet->assign(a, a + MAXN);

			//����
			make_heap(pvet->begin(), pvet->end());
			PrintfVectorInt(*pvet);

			//���������� ���������м��룬�ٵ���push_heap()
			pvet->push_back(25);
			push_heap(pvet->begin(), pvet->end());
			PrintfVectorInt(*pvet);

			//ɾ������  Ҫ�ȵ���pop_heap()������������ɾ��
			pop_heap(pvet->begin(), pvet->end());
			pvet->pop_back();
			pop_heap(pvet->begin(), pvet->end());
			pvet->pop_back();
			PrintfVectorInt(*pvet);

			//������
			sort_heap(pvet->begin(), pvet->end());
			PrintfVectorInt(*pvet);

			delete pvet;
			return 0;
		}
		//Contains Duplicate II,ʹ��unordered_map<int,vector<int>>�ڴ泬��
		bool containsNearbyDuplicate(vector<int>& nums, int k)
		{
			int length = nums.size();
			if (length == 0 || k == 0)
				return false;
			//��vector<int>����¼nums[i]���ֵ�λ������
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
		//Contains Duplicate II,ֱ��ʹ������forѭ����ʱ
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
		//Contains Duplicate II��ʹ�ù�����unordered_map<int,int>,��ac
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
		//Contains Duplicate III��ֱ��ʹ��sort����
		bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
		{
			if (nums.size() < 2) return false;
			vector<pair<long, int>> v;
			for (int i = 0; i < nums.size(); i++)
			{
				v.push_back(pair<long, int>((long)nums[i], i));
			}
			//����
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
		//Contains Duplicate III,ʹ��multimap���򣬺������˼��һ��
		//reference��https://leetcode.com/discuss/60011/c-28ms-solution-using-multimap
		bool containsNearbyAlmostDuplicate_multimap(vector<int>& nums, int k, int t)
		{
			multimap<long, int> map;
			//����multimap������
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
		//Rectangle Area,���������ε�ȫ���������
		int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
		{
			int x = get_union(A, C, E, G);
			int y = get_union(B, D, F, H);

			int area1 = abs((A - C)*(B - D));
			int area2 = abs((E - G)*(F - H));
			return area1 + area2 - x*y;
		}
		//������[x1,x2]������[x3,x4]֮��Ľ�������
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
		//����������չ������sign_vec����¼���ű任��result��¼������
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
		//ֱ�������򣬺󿽱�,ʱ�临�Ӷ�O(N*logN)���ռ临�Ӷ�O(N)
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
		//ʱ�临�Ӷ�O(N)���ռ临�Ӷ�O(1)��ʹ��nth_element�㷨��three_way partition����
		//�ο� https://leetcode.com/discuss/77133/o-n-o-1-after-median-virtual-indexing
		//��������������ο���http://www.cnblogs.com/gnuhpc/archive/2012/12/21/2828166.html
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
		//Summary Ranges����ķ�����0ms
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
		//Power of Two���ж��Ƿ���2����
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
		//��log�����㣬�ж��Ƿ���3����
		bool isPowerOfThree(int n)
		{
			if(n<=0)
				return false;
			const double ratio = 1/log2(3);
			double diff = log2(n)*ratio;
			//�����3���ݣ���diffӦ��Ϊ����
			return abs(diff-round(diff))<1e-13;
		}
		//ѭ����
		bool isPowerOfThree_v2(int n) 
		{
			if(n>1)
				while(n%3==0) n /= 3;
			return n==1;
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

	vector<vector<char>> vec1 = {
		{ '0', '0', '0', '1'},
		{ '1', '1', '0', '1'},
		{ '1', '1', '1', '1'},
		{ '0', '1', '1', '1'},
		{ '0', '1', '1', '1'}
	};
	vector<int> vec = { 0,1,2,4,5,7 };
	panzg_leetcode::Solution sol;

	string s = "(1+(4+5+2)-3)+(6+8)";
	auto res = sol.summaryRanges(vec);
	for each (auto var in res)
	{
		cout << var << " ";
	}
	getchar();
}
#endif