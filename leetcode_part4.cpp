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
		// Basic Calculator II,��ջ
		int calculate_2(string s)
		{
			stack<int> ele_stack;
			int length = s.length();
			char sign = '+';
			int num = 0;
			for (int i = 0; i < length;i++)
			{
				//��������
				if (isdigit(s[i]))
				{
					num = num * 10 + s[i] - '0';
				}
				//�Ӽ��˳�
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
			//�ۼ�
			int result = num;
			while (!ele_stack.empty())
			{
				result += ele_stack.top();
				ele_stack.pop();
			}
			return result;
		}
		//Count Complete Tree Nodes��ֱ�Ӳ�α�������ʱ
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
		//�ݹ鷽�����ο���https://leetcode.com/discuss/73892/a-very-clear-recursive-solution-isnt-it
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
		//�����������
		int countNodes_helper(TreeNode* root)
		{
			if (root == nullptr)
				return 0;
			else
				return 1 + countNodes_helper(root->left);
		}
		//Expression Add Operators, https://leetcode.com/problems/expression-add-operators/
		//DFS�������������
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
		//dfs����
		//result-->������;cur-->Ŀǰ���ַ�����pos-->Ŀǰλ�ã�cv-->Ŀǰֵ��pv-->ǰһ����������op-->��һ��������
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
		//ֱ�ӵݹ飬ʱ�临�Ӷ�O(N)���ռ临�Ӷ�O(N)
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
			//���������˼·
			kthSmallest_helper(root->left, result, k);
			if (result.size() == k)
				return;
			else
				result.push_back(root->val);
			kthSmallest_helper(root->right, result, k);
		}
		//���õݹ飬��ջ��ʱ�临�Ӷ�O(N)���ռ临�Ӷ�O(N)
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
		//������ջ��ʵ�ֶ���
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
		//ֱ�ӱ�������ʱ
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
		//��ѧ�⣬�ҹ��ɣ�����ѧ֮���������ӣ�http://www.cppblog.com/myjfm/archive/2012/09/04/189444.html
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
		//ֱ����ջ��ˮ�������ǿռ临�Ӷ�ΪO(N)
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
		//Palindrome Linked List,�����ҵ�������м�ڵ㣬��ǰ�벿���������ã�����ָ��������αȽ�,�ռ临�Ӷ�ΪO(1)
		bool isPalindrome_v2(ListNode* head)
		{
			int count_length = 0;
			ListNode* cur = head;
			ListNode* reverse_head;
			int low_step = 0;
			//��������������
			while (cur)
			{
				count_length++;
				cur = cur->next;
			}
			
			//��ȡ��벿�ֵ���ָ��
			cur = head;
			int i = 0;
			int len = (count_length % 2) == 0 ? count_length / 2 : count_length / 2 + 1;
			while (i< len)
			{
				i++;
				cur = cur->next;
			}

			//��ת����Ϊcount_length/2������
			reverse_head = reverse_list_by_length(head, count_length/2);

			//ǰ�����˱Ƚ�
			while (cur!=nullptr && reverse_head != nullptr)
			{
				if(cur->val != reverse_head->val)
					return false;
				cur = cur->next;
				reverse_head = reverse_head->next;
			}
			return true;
		}

		//���ݳ�������ת����
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
		// ����������е�LCA���⣬ֱ�ӵݹ�
		TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
		{
			if (p->val<root->val && q->val < root->val)
				return lowestCommonAncestor(root->left, p, q);
			if (p->val > root->val && q->val>root->val)
				return lowestCommonAncestor(root->right, p, q);
			return root;
		}
		//Lowest Common Ancestor of a Binary Tree,https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
		//�������е�LCA���⣬�ݹ���
		TreeNode* lowestCommonAncestor_2(TreeNode* root, TreeNode* p, TreeNode* q)
		{
			if (!root || root == p || root == q)
				return root;
			TreeNode* left = lowestCommonAncestor_2(root->left, p, q);
			TreeNode* right = lowestCommonAncestor_2(root->right, p, q);
			//���1��p&q�ڵ㶼��root������
			if (left == nullptr)
				return right;
			else
			{
				//���2��p��q����root��������
				if (right == nullptr)
					return left;
				//���3��p��q�ֱ���root����������
				else
					return root;
			}
		}
		//Add Digits,Digital Root���⣬�ⷨ1���£�
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
		//�ⷨ2��reference:http://my.oschina.net/Tsybius2014/blog/497645
		int addDigits_v2(int num) 
		{
			return (num - 1) % 9 + 1;
		}
		//Product of Array Except Self,�ⷨ1��ֱ�ӱ��������Ӷ�O(N*N)����ʱ
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
		//Product of Array Except Self,�ⷨ2����������������¼ǰ�����˵ĳ˻�
		vector<int> productExceptSelf_v2(vector<int>& nums)
		{
			//��¼ǰi��Ԫ�صĳ˻�
			vector<int> from_begin_product(nums.size());
			//��¼��i��Ԫ�صĳ˻�
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
				//result[i]����ǰi��Ԫ�غͺ�size-1-i��Ԫ�صĳ˻�
				result[i] = from_begin_product[i] * from_end_product[nums.size()-1 - i];
			}
			return result;
		}
		//Sliding Window Maximum,https://leetcode.com/problems/sliding-window-maximum/
		//ֱ���жϣ�ʱ�临�Ӷ�ΪO(N*N)
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
		//deque�����ñ�����,ʱ�临�Ӷ�ΪO(N)
		vector<int> maxSlidingWindow_v2(vector<int>& nums, int k)
		{
			vector<int> ret;
			deque<int> max;
			for (int i = 0; i < nums.size(); ++i) 
			{
				//����ǰֵ������������ֵ
				while (!max.empty() && nums[i] > max.back()) 
				{
					max.pop_back();
				}
				max.push_back(nums[i]);
				//�ӵ�k��Ԫ�ؿ�ʼѹ�뷵��ֵ
				if (i >= k - 1) 
				{
					ret.push_back(max.front());
					//�����ǰ���ڵ����ֵ�Ǹô��ڵĵ�һ��ֵ������Ҫ����
					if (nums[i - k + 1] == max.front()) 
					{
						max.pop_front();
					}
				}
			}
			return ret;
		}
		//Binary Tree Paths,https://leetcode.com/problems/binary-tree-paths/
		//�����дӸ��ڵ㵽Ҷ�ӽڵ��·����DFS����
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
		//Ugly Number II��https://leetcode.com/problems/ugly-number-ii/
		//ֱ�Ӳ��ҵ�n����������ʱ
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
		//��DP�㷨���,
		int nthUglyNumber_dp(int n)
		{
			if (n == 1)
				return 1;
			vector<int> ret(n);
			ret[0] = 1;
			//ָ��2,3,5������
			int p2_idx = 0, p3_idx = 0, p5_idx = 0;
			for (int i = 1; i < n;i++)
			{
				ret[i] = min(ret[p2_idx] * 2, min(ret[p3_idx] * 3, ret[p5_idx] * 5));
				//����ǰ��
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
		//λ����,��ȫ����������㣬�õ�a^b��Ȼ����a^bĳλΪ1������Ϊ0�������ٱ���һ�����飬����ʱ��������a��b�е�һ����
		//��󣬽��õ���������a^b��������һ������
		vector<int> singleNumber(vector<int>& nums)
		{
			vector<int> ret(2);
			int res1 = 0, res2 = 0;
			for (int i = 0; i < nums.size(); i++)
			{
				res1 ^= nums[i];
			}
			//tempֻ����a^b�����ҵ�1��������0
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
		//ֱ��������ʱ�临�Ӷ�ΪO(N*N)
		int missingNumber(vector<int>& nums)
		{
			if (nums.size() == 0)
				return 0;
			//����
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
		//ʱ�临�Ӷ�ΪO(N)������ο���������ָ�ϡ�P386
		int missingNumber_v2(vector<int>& nums)
		{
			int l = 0;
			int r = nums.size();
			while (l<r)
			{
				if (nums[l] == l)
					l++;
				else if (nums[l] <= l-1 || nums[l]>r-1 || nums[nums[l]] == nums[l])
					nums[l] = nums[--r];
				else
					swap(nums[l], nums[nums[l]]);
			}
			return l;
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

	panzg_leetcode::Solution sol;


	TreeNode node1(1);
	ListNode node2(2);
	ListNode node3(3);
	ListNode node4(2);
	ListNode node5(1);
	node1.left = nullptr;
	node1.right = nullptr;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	
	vector<int> vec = { 1,0};
	auto ret = sol.missingNumber_v2(vec);
	cout << ret;

	system("pause");
}
#endif