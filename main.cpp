#include"header.h"
using namespace std;
class Solution
{
private:
	int ** new_matrix(int n, int m)
	{
		int **p;
		p = new int*[n];
		for (size_t i = 0; i < n; i++)
		{
			p[i] = new int[m];
		}
		return p;
	}
	void delete_matrix(int **p, int n)
	{
		for (size_t i = 0; i < n; i++)
		{
			delete[] p[i];
		}
		delete[] p;
	}
	static unsigned int binary_to_gray(unsigned int n)
	{

		return n ^ (n >> 1);
	}
	int factorial(int n)
	{
		int result = 1;
		for (int i = 1; i <= n; ++i)
			result *= i;
		return result;
	}
	// seq 已排好序，是第一个排列
	template<typename Sequence>
	Sequence kth_permutation(const Sequence &seq, int k)
	{
		const int n = seq.size();
		Sequence S(seq);
		Sequence result;
		int base = factorial(n - 1);
		--k; // 康托编码从 0 开始
		for (int i = n - 1; i > 0; k %= base, base /= i, --i)
		{
			auto a = next(S.begin(), k / base);
			result.push_back(*a);
			S.erase(a);
		}
		result.push_back(S[0]); // 最后一个
		return result;
	}
	vector<int>& generate_data()
	{
		vector<int> ivec(10);
		iota(ivec.begin(), ivec.end(), 1);

		std::random_device rd;
		std::mt19937 g(rd());
		shuffle(ivec.begin(), ivec.end(), g);
		for each (auto var in ivec)
		{
			cout << "  " << var;
		}
		return ivec;
	}
	string& trim(string &s)
	{
		if (s.empty())
		{
			return s;
		}
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
		return s;
	}
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
	// 逆转路径
	static void tree_reverse(TreeNode *from, TreeNode *to)
	{
		TreeNode *x = from, *y = from->right, *z;
		if (from == to) return;
		while (x != to)
		{
			z = y->right;
			y->right = x;
			x = y;
			y = z;
		}
	}
	// 访问逆转后的路径上的所有结点
	static void visit_reverse(TreeNode* from, TreeNode *to,
		std::function< void(const TreeNode*) >& visit)
	{
		TreeNode *p = to;
		reverse(from, to);
		while (true)
		{
			visit(p);
			if (p == from)
				break;
			p = p->right;
		}
		reverse(to, from);
	}
public:
	vector<int> twoSum(vector<int> &num, int target)
	{
		unordered_map<int, int> mapping;
		vector<int> result;
		for (int i = 0; i < num.size(); i++)
		{
			mapping[num[i]] = i;
		}
		for (int i = 0; i < num.size(); i++)
		{
			const int gap = target - num[i];
			if (mapping.find(gap) != mapping.end() && mapping[gap] > i)
			{
				result.push_back(i + 1);
				result.push_back(mapping[gap] + 1);
				break;
			}
		}
		return result;
	}
	vector<vector<int>> threeSum(vector<int>& num)
	{
		vector<vector<int>> result;
		if (num.size() < 3) return result;
		sort(num.begin(), num.end());
		const int target = 0;
		auto last = num.end();
		for (auto i = num.begin(); i < last - 2; ++i)
		{
			auto j = i + 1;
			if (i > num.begin() && *i == *(i - 1)) continue;
			auto k = last - 1;
			while (j < k)
			{
				if (*i + *j + *k < target)
				{
					++j;
					while (*j == *(j - 1) && j < k) ++j;
				}
				else if (*i + *j + *k > target)
				{
					--k;
					while (*k == *(k + 1) && j < k) --k;
				}
				else
				{
					result.push_back({ *i, *j, *k });
					++j;
					--k;
					while (*j == *(j - 1) && *k == *(k + 1) && j < k) ++j;
				}
			}
		}
		return result;
	}
	int threeSumClosest(vector<int> &num, int target)
	{
		int result = 0;
		int min_gap = INT_MAX;
		sort(num.begin(), num.end());
		for (auto a = num.begin(); a != prev(num.end(), 2); a++)
		{
			auto b = next(a);
			auto c = prev(num.end());
			while (b < c)
			{
				const int sum = *a + *b + *c;
				const int gap = abs(sum - target);
				if (gap < min_gap)
				{
					result = sum;
					min_gap = gap;
				}
				if (sum < target)
				{
					++b;
				}
				else
					--c;
			}
		}
		return result;
	}
	/// leetcode , fourSum,用unordered_multimap,超时
	vector<vector<int>> fourSum(vector<int> &num, int target)
	{
		vector<vector<int>> result;
		if (num.size() < 4)
			return result;
		sort(num.begin(), num.end());
		unordered_multimap<int, pair<int, int>> cache;
		for (size_t i = 0; i < num.size(); ++i)
		{
			for (size_t j = i + 1; j < num.size(); ++j)
			{
				cache.insert(make_pair(num[i] + num[j], make_pair(i, j)));
			}
		}
		for (auto i = cache.begin(); i != cache.end(); ++i)
		{
			int gap = target - i->first;
			auto find_range = cache.equal_range(gap);
			for (auto j = find_range.first; j != find_range.second; j++)
			{
				auto a = i->second.first;
				auto b = i->second.second;
				auto c = j->second.first;
				auto d = j->second.second;

				if (a != c&&a != d&&b != c&&b != d)
				{
					vector < int > vec = { num[a], num[b], num[c], num[d] };
					sort(vec.begin(), vec.end());
					result.push_back(vec);
				}
			}
		}
		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;

	}
	//leetcode,4sum,用unodered_map，不超时
	vector<vector<int>> fourSum_v2(vector<int> &num, int target)
	{
		vector<vector<int>> result;
		if (num.size() < 4) return result;
		sort(num.begin(), num.end());
		unordered_map<int, vector<pair<int, int> > > cache;
		for (size_t a = 0; a < num.size(); ++a)
		{
			for (size_t b = a + 1; b < num.size(); ++b)
			{
				cache[num[a] + num[b]].push_back(pair<int, int>(a, b));
			}
		}
		for (int c = 0; c < num.size(); ++c)
		{
			for (size_t d = c + 1; d < num.size(); ++d)
			{
				const int key = target - num[c] - num[d];
				if (cache.find(key) == cache.end()) continue;
				const auto& vec = cache[key];
				for (size_t k = 0; k < vec.size(); ++k)
				{
					if (c <= vec[k].second)
						continue; // 有重叠
					result.push_back({ num[vec[k].first],
						num[vec[k].second], num[c], num[d]
					});
				}
			}
		}
		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;
	}
	//leetcode,remove element
	int removeElement(vector<int> &nums, int val)
	{
		int index = 0;
		vector<int> vec;
		for (size_t i = 0; i < nums.size(); i++)
		{
			if (nums[i] != val)
			{
				vec.push_back(nums[i]);
				index++;
			}
		}
		vec.swap(nums);
		return index;
	}
	/**
	* @param nums: a vector of integers
	* @return: return nothing (void), do not return anything, modify nums in-place instead
	*/
	void nextPermutation(vector<int> &nums)
	{
		// write your code here
		int n = nums.size();
		for (int i = n - 1; i >= 0; i--)
		{
			for (int j = n - 1; j > i; j--)
			{
				if (nums[i] < nums[j])
				{
					swap(nums[i], nums[j]);
					sort(nums.begin() + i + 1, nums.end());
					return;
				}
			}
		}
		sort(nums.begin(), nums.end());
	}
	/*permutation_sequence 暴力破解法 超时*/
	string permutation_sequence(const int n, const int k)
	{
		string str(n, '0');
		for (size_t i = 0; i < n; i++)
		{
			str[i] += (i + 1);
		}
		for (size_t i = 1; i < k; i++)
		{
			next_permutation(str.begin(), str.end());
		}
		return str;
	}
	/*permutation sequence 康托序列时间复杂度 O(n)，空间复杂度 O(1) */
	string getPermutation(int n, int k)
	{
		string s(n, '0');
		string result;
		for (int i = 0; i < n; ++i)
			s[i] += i + 1;
		return kth_permutation(s, k);
	}
	/*trapping rain water*/
	int trap(int A[], int n)
	{
		int *left_flag = new int[n];
		int *right_flag = new  int[n];
		memset(left_flag, INT_MAX, n*sizeof(int));
		memset(right_flag, INT_MAX, n* sizeof(int));
		left_flag[0] = 0;
		right_flag[n - 1] = 0;

		//扫描左边
		for (int i = 1; i < n; i++)
		{
			if (A[i - 1]>left_flag[i - 1])
			{
				left_flag[i] = A[i - 1];
			}
			else
			{
				left_flag[i] = left_flag[i - 1];
			}
		}
		//扫描右边
		for (int i = n - 2; i >= 0; i--)
		{
			if (A[i + 1] > right_flag[i + 1])
				right_flag[i] = A[i + 1];
			else
				right_flag[i] = right_flag[i + 1];
		}

		int result = 0;
		for (size_t i = 0; i < n; i++)
		{
			int compare = min(left_flag[i], right_flag[i]) - A[i];
			result += (compare>0 ? compare : 0);
		}

		delete[] left_flag;
		delete[] right_flag;
		return result;
	}
	/*trapping train water v2*/
	int trap(vector<int> &height)
	{
		int result = 0;
		int n = height.size();
		int *left_flag = new int[n];
		int *right_flag = new  int[n];
		memset(left_flag, INT_MAX, n*sizeof(int));
		memset(right_flag, INT_MAX, n* sizeof(int));
		left_flag[0] = 0;
		right_flag[n - 1] = 0;

		//扫描左边
		for (int i = 1; i < n; i++)
		{
			if (height[i - 1]>left_flag[i - 1])
			{
				left_flag[i] = height[i - 1];
			}
			else
			{
				left_flag[i] = left_flag[i - 1];
			}
		}
		//扫描右边
		for (int i = n - 2; i >= 0; i--)
		{
			if (height[i + 1] > right_flag[i + 1])
				right_flag[i] = height[i + 1];
			else
				right_flag[i] = right_flag[i + 1];
		}

		for (size_t i = 0; i < n; i++)
		{
			int compare = min(left_flag[i], right_flag[i]) - height[i];
			result += (compare>0 ? compare : 0);
		}

		delete[] left_flag;
		delete[] right_flag;
		return result;
	}
	/*
	rotate image
	时间复杂度 O(n^2)，空间复杂度 O(1)
	*/
	void rotate(vector<vector<int>> &matrix)
	{
		int n = matrix.size();
		//转置矩阵
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < i; j++)
			{
				swap(matrix[i][j], matrix[j][i]);
			}
		}
		//左右翻转
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n / 2; j++)
			{
				swap(matrix[i][j], matrix[i][n - 1 - j]);
			}
		}
	}
	/*climbing stairs*/
	int climbStairs(int n)
	{
		int pre1 = 1, pre2 = 1;
		int cur = 0;
		if (n == 0)
		{
			return pre1;
		}
		if (n == 1)
		{
			return pre2;
		}
		for (size_t i = 2; i <= n; i++)
		{
			cur = pre1 + pre2;
			pre1 = pre2;
			pre2 = cur;
		}
		return cur;
	}
	vector<int> grayCode(int n)
	{
		vector<int> result;
		const size_t size = 1 << n; // 2^n
		result.reserve(size);
		for (size_t i = 0; i < size; ++i)
			result.push_back(i ^ (i >> 1));
		return result;
	}
	/*空间复杂度为O(m+n)*/
	void setZeros(vector<vector<int>> &matrix)
	{
		int rows = matrix.size();
		int colums = matrix[0].size();
		int *row_flags = new int[rows];
		int *colum_flags = new int[colums];
		memset(row_flags, 1, rows*sizeof(int));
		memset(colum_flags, 1, colums*sizeof(int));
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < colums; j++)
			{
				if (matrix[i][j] == 0)
				{
					row_flags[i] = colum_flags[j] = 0;
				}
			}
		}
		for (size_t i = 0; i < rows; i++)
		{
			if (row_flags[i] == 0)
			{
				for (size_t j = 0; j < colums; j++)
				{
					matrix[i][j] = 0;
				}
			}
		}
		for (size_t i = 0; i < colums; i++)
		{
			if (colum_flags[i] == 0)
			{
				for (size_t j = 0; j < rows; j++)
				{
					matrix[j][i] = 0;
				}
			}
		}
	}
	/*
	*空间复杂度为O（1）
	*复用第一行和第一列，先标记第一行和第一列是否有0元素，然后遍历矩阵，如果有0就将该元素的行列第一个元素标记为0.
	*/
	void setZeros_v2(vector<vector<int>> &matrix)
	{
		int rows = matrix.size();
		int colums = matrix[0].size();
		int first_rows_have_zero = 0, first_colum_have_zero = 0;
		//标记第一行是否有0元素
		for (size_t i = 0; i < colums; i++)
		{
			if (matrix[0][i] == 0)
			{
				first_rows_have_zero = 1;
				break;
			}
		}
		//标记第一列是否有0元素
		for (size_t i = 0; i < rows; i++)
		{
			if (matrix[i][0] == 0)
			{
				first_colum_have_zero = 1;
				break;
			}
		}
		//复用第一行和第一列，如果有0元素就将该元素的行列第一个元素置0
		for (size_t i = 1; i < rows; i++)
		{
			for (size_t j = 1; j < colums; j++)
			{
				if (matrix[i][j] == 0)
				{
					matrix[0][j] = 0;
					matrix[i][0] = 0;
				}
			}
		}
		//遍历，如果第一行第一列的元素为0，则该元素应为0
		for (size_t i = 1; i < rows; i++)
		{
			for (size_t j = 1; j < colums; j++)
			{
				if (matrix[0][j] == 0 || matrix[i][0] == 0)
				{
					matrix[i][j] = 0;
				}
			}
		}
		//讨论第一列是否含0
		if (first_colum_have_zero)
		{
			for (size_t i = 0; i < rows; i++)
			{
				matrix[i][0] = 0;
			}
		}
		//讨论第一行是否含0
		if (first_rows_have_zero)
		{
			for (size_t i = 0; i < colums; i++)
			{
				matrix[0][i] = 0;
			}
		}
	}
	/*题意不明*/
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
	{
		int total = 0;
		int j = -1;
		for (int i = 0, sum = 0; i < gas.size(); ++i)
		{
			sum += gas[i] - cost[i];
			total += gas[i] - cost[i];
			if (sum < 0)
			{
				j = i;
				sum = 0;
			}
		}
		return total >= 0 ? j + 1 : -1;
	}
	/*candy*/
	int candy(vector<int> &rating)
	{
		int number = rating.size();
		vector<int> candy(number, 1);

		int inc = 2;
		for (int i = 1; i < number; i++)
		{
			if (rating[i]>rating[i - 1])
			{
				candy[i] = max(candy[i], inc++);
			}
			else
				inc = 2;
		}
		inc = 2;
		for (int i = number - 2; i >= 0; i--)
		{
			if (rating[i] > rating[i + 1])
			{
				candy[i] = max(candy[i], inc++);
			}
			else
				inc = 2;
		}
		return accumulate(candy.begin(), candy.end(), 0);
	}
	/*singleNumber*/
	int singleNumber(vector<int> &nums)
	{
		unordered_map<int, int> my_map;
		for (size_t i = 0; i < nums.size(); i++)
		{
			auto ret = my_map.insert({ nums[i], 1 });
			if (!ret.second)
				++ret.first->second;
		}
		for (size_t i = 0; i < nums.size(); i++)
		{
			if (my_map[nums[i]] != 2)
				return nums[i];
		}
	}
	/*不使用额外的空间*/
	int singleNumber(vector<int> &nums, int flag = 0)
	{
		int x = 0;
		for (size_t i = 0; i < nums.size(); ++i)
			x ^= nums[i];
		return x;
	}
	int singleNumber2(vector<int> &nums)
	{
		unordered_map<int, int> my_map;
		for (size_t i = 0; i < nums.size(); i++)
		{
			auto ret = my_map.insert({ nums[i], 1 });
			if (!ret.second)
				++ret.first->second;
		}
		for (size_t i = 0; i < nums.size(); i++)
		{
			if (my_map[nums[i]] != 3)
				return nums[i];
		}
	}
	/*add two number*/
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		ListNode val(-1);
		int carry = 0;
		ListNode *result_header = &val;
		for (ListNode *ptr1 = l1, *ptr2 = l2;
			ptr1 != nullptr || ptr2 != nullptr;
			ptr1 = (ptr1 == nullptr ? nullptr : ptr1->next),
			ptr2 = (ptr2 == nullptr ? nullptr : ptr2->next),
			result_header = result_header->next)
		{
			const int val_a = ptr1 == nullptr ? 0 : ptr1->val;
			const int val_b = ptr2 == nullptr ? 0 : ptr2->val;
			const int value = (val_a + val_b + carry) % 10;
			carry = (val_a + val_b + carry) / 10;

			result_header->next = new ListNode(value);
		}
		if (carry > 0)
		{
			result_header->next = new ListNode(carry);
		}
		return val.next;
	}
	ListNode *addTwoNumbers2(ListNode *l1, ListNode *l2)
	{
		ListNode dummy(-1); // 头节点
		int carry = 0;
		ListNode *prev = &dummy;
		for (ListNode *pa = l1, *pb = l2;
			pa != nullptr || pb != nullptr;
			pa = pa == nullptr ? nullptr : pa->next,
			pb = pb == nullptr ? nullptr : pb->next,
			prev = prev->next)
		{
			const int ai = pa == nullptr ? 0 : pa->val;
			const int bi = pb == nullptr ? 0 : pb->val;
			const int value = (ai + bi + carry) % 10;
			carry = (ai + bi + carry) / 10;
			prev->next = new ListNode(value); // 尾插法
		}
		if (carry > 0)
			prev->next = new ListNode(carry);
		return dummy.next;
	}
	/*Reverse Linked List II*/
	ListNode* reverseBetween(ListNode* head, int m, int n)
	{
		if (n == m)
		{
			return head;
		}
		ListNode *myhead = new ListNode(-1);
		myhead->next = head;
		ListNode *pre = myhead;
		int count = 1;
		while (count != m)
		{
			pre = pre->next;
			count++;
		}
		ListNode *first = pre->next;
		ListNode *second = first->next;
		while (count < n)
		{
			first->next = second->next;
			second->next = pre->next;
			pre->next = second;
			second = first->next;
			count++;
		}
		return myhead->next;
	}
	/*Partition List*/
	ListNode* partition(ListNode* head, int x)
	{
		ListNode *my_header_less = new ListNode(-1);
		ListNode *my_header_more = new ListNode(-1);
		ListNode *temp;
		ListNode *tail_less = my_header_less;
		ListNode *tail_more = my_header_more;
		while (head != nullptr)
		{
			temp = head->next;
			if (head->val < x)
			{
				tail_less->next = head;
				tail_less = head;
				head->next = nullptr;
			}
			else
			{
				tail_more->next = head;
				tail_more = head;
				head->next = nullptr;
			}
			head = temp;
		}
		tail_less->next = my_header_more->next;
		return my_header_less->next;
	}
	ListNode *rotateRight(ListNode *head, int k)
	{
		if (head == nullptr || k == 0) return head;
		int len = 1;
		ListNode* p = head;
		while (p->next)   // 求长度
		{
			len++;
			p = p->next;
		}
		k = len - k % len;
		p->next = head; // 首尾相连
		for (int step = 0; step < k; step++)
		{
			p = p->next; //接着往后跑
		}
		head = p->next; // 新的首节点
		p->next = nullptr; // 断开环
		return head;
	}
	/*remove nth from end ,用前后两个指针*/
	ListNode* removeNthFromEnd(ListNode *head, int n)
	{
		ListNode *myhead = new ListNode(-1);
		myhead->next = head;
		ListNode* pre = nullptr, *nextptr = nullptr;
		int count = 0;
		nextptr = myhead;
		pre = myhead;
		while (count != n && nextptr != nullptr)
		{
			nextptr = nextptr->next;
			count++;
		}
		while (nextptr != nullptr&&nextptr->next != nullptr&&pre != nullptr&&pre->next != nullptr)
		{
			nextptr = nextptr->next;
			pre = pre->next;
		}
		pre->next = pre->next->next;
		return myhead->next;
	}
	/*自己写的冒泡排序*/
	void bubblesort(vector<int> &ivec)
	{
		int swap;
		int flag = 1;
		int num = ivec.size();
		for (int i = num - 1; i > 0 && flag; i--)
		{
			flag = 0;
			for (int j = 0; j < i; j++)
			{
				if (ivec[j]>ivec[j + 1])
				{
					swap = ivec[j];
					ivec[j] = ivec[j + 1];
					ivec[j + 1] = swap;
					flag = 1;
				}
			}
		}
	}
	int minimumTotal(vector<vector<int>>& triangle)
	{
		for (int i = triangle.size() - 2; i >= 0; i--)
		{
			for (size_t j = 0; j < i + 1; j++)
			{
				triangle[i][j] = min(triangle[i + 1][j], triangle[i + 1][j + 1]) + triangle[i][j];
			}
		}
		return triangle[0][0];
	}

	int maxSubArray(int A[], int n)
	{
		int result = INT_MIN, f = 0;
		for (int i = 0; i < n; ++i)
		{
			f = max(f + A[i], A[i]);
			result = max(result, f);
		}
		return result;
	}
	bool isPalindrome(string s)
	{
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		auto left = s.begin();
		auto right = prev(s.end());
		while (left < right)
		{
			if (!isalnum(*left)) left++;
			else if (!isalnum(*right)) right--;
			else if (*left == *right) { left++; right--; }
			else return false;
		}
		return true;
	}
	int strStr(string haystack, string needle)
	{
		if (needle == "") return 0;
		int index_long = haystack.size() - needle.size();
		int i, j;
		for (i = 0; i <= index_long; i++)
		{
			for (j = 0; j < needle.size(); j++)
			{
				if (needle[j] != haystack[i + j])
					break;
			}
			if (j == needle.size()) return i;
		}
		return -1;
	}

	int myAtoi(string str)
	{
		int i = 0, sign = 1;
		long int num = 0;

		//remove the whitespaces
		while (isspace(str[i])) i++;

		//get the sign
		if ('+' == str[i]) i++;
		else if ('-' == str[i]) {
			sign = -1;
			i++;
		}

		//create the number
		while (str[i] >= '0' && str[i] <= '9') {
			num = num * 10 + str[i] - '0';

			//if outside the limit, return limit
			if (sign*num > INT_MAX) return INT_MAX;
			else if (sign*num < INT_MIN) return INT_MIN;

			i++;
		}
		//ignore the other chars

		return (int)sign*num;
	}
	/*add Binary*/
	string addBinary(string a, string b)
	{
		string result;
		int n = a.size() > b.size() ? a.size() : b.size();
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		int carry = 0;

		for (size_t i = 0; i < n; i++)
		{
			const int ai = i < a.size() ? a[i] - '0' : 0;
			const int bi = i < b.size() ? b[i] - '0' : 0;
			const int val = ai + bi + carry;
			carry = val / 2;
			result.insert(result.begin(), val % 2 + '0');
		}
		if (carry > 0)
			result.insert(result.begin(), '1');
		return result;
	}

	/*Longest Palindromic Substring
	*简单动态规划
	f(i, j) =  |- true && i==j
	|- s[i]==s[j]&&i+1==j
	|- s[i]==s[j]&&i+1<j&&f[i+1][j-1]
	*复杂度为O(N^2),另外有Manacher’ s Algorithm算法，为O(n)，难以理解
	*/
	string longestPalindrome(string s)
	{
		int _size = s.size();
		int start = 0, lenght = 1;
		int *matrix = new int[_size*_size];
		memset(matrix, 0, _size*_size*sizeof(int));
		for (size_t i = 0; i < _size; i++)
		{
			matrix[i*_size + i] = 1;
		}
		//注意这里的遍历顺利，第i个状态依赖于i+1个状态
		for (int i = _size - 1; i >= 0; i--)
		{
			for (size_t j = i; j < _size; j++)
			{
				if (i == j)
					matrix[i*_size + j] = 1;
				else if ((i + 1 == j) && (s[i] == s[j]))
				{
					matrix[i*_size + j] = 1;
					if (lenght < 2)
					{
						start = i;
						lenght = 2;
					}
				}
				else if ((i + 1 < j) && (s[i] == s[j]) && (matrix[(i + 1)*_size + j - 1]))
				{
					matrix[i*_size + j] = 1;
					if (lenght < (j - i + 1))
					{
						lenght = (j - i + 1);
						start = i;
					}
				}
			}
		}
		delete[] matrix;
		return s.substr(start, lenght);
	}

	/*蘑菇街 求最长公共子序列*/
	int LCS(string str)
	{
		string a = str;
		string b = str;
		//反转字符串，变成求最长公共子序列问题
		std::reverse(b.begin(), b.end());
		int len1 = a.size();
		int len2 = b.size();
		int dp[3][11];  //这里最大10个字符长度的字符串
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= len1; i++)
		{
			for (int j = 1; j <= len2; j++)
			{
				dp[0][j] = dp[1][j]; //滚动数组节省内存
				dp[1][j] = dp[2][j];
				if (a[i - 1] == b[j - 1])
					dp[1][j] = dp[0][j - 1] + 1;
				else
					dp[1][j] = max(dp[0][j], dp[1][j - 1]);
			}
		}
		return dp[1][len2];
	}
	/*蘑菇街*/
	void lcw_v2()
	{
		string str;
		while (cin >> str)
		{
			string a = str;
			string b = str;
			int len1 = a.size();
			int len2 = b.size();
			int begin = 0, end = len1 - 1;
			while (begin < end)
			{
				char temp = b[begin];
				b[begin] = b[end];
				b[end] = temp;
				++begin;
				--end;
			}

			//反转字符串，变成求最长公共子序列问题
			//std::reverse(b.begin(), b.end());
			int dp[3][10];
			memset(dp, 0, sizeof(dp));
			for (int i = 1; i <= len1; i++)
			{
				for (int j = 1; j <= len2; j++)
				{
					dp[0][j] = dp[1][j]; //滚动数组节省内存
					dp[1][j] = dp[2][j];
					if (a[i - 1] == b[j - 1])
						dp[1][j] = dp[0][j - 1] + 1;
					else
						dp[1][j] = max(dp[0][j], dp[1][j - 1]);
				}
			}
			//如果距离为1，则可以添加一个字母变成回文,否则不能。这里dp[1][len2]表示公共子序列大小
			if (len1 - dp[1][len2] == 1)
				cout << "YES" << endl;
			else
				cout << "N0" << endl;
		}

	}
	/*圆的旋转问题，求移动圆心的步骤*/
	void yuan()
	{
		long r, x, y, x1, y1;
		while (cin >> r >> x >> y >> x1 >> y1)
		{
			//求与2r的关系，结果就是步数
			long dis = sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y));
			int ratio = ceil(dis / (2 * r));
			cout << ratio << endl;
		}
	}
	/* Palindrome Partitioning II 动态规划 */
	int minCut(string s)
	{
		const int lenght = s.size();
		int *f = new int[lenght + 1];
		int **p = new int*[lenght];
		for (size_t i = 0; i < lenght; i++)
		{
			p[i] = new int[lenght];
			memset(p[i], 0, lenght*sizeof(int));
		}
		for (size_t i = 0; i < lenght; i++)
		{
			for (size_t j = 0; j < lenght; j++)
			{
				cout << " " << p[i][j];
			}
			cout << "\n";
		}
		for (size_t i = 0; i <= lenght; i++)
		{
			f[i] = lenght - 1 - i;
		}
		for (int i = lenght - 1; i >= 0; i--)
		{
			for (int j = i; j < lenght; j++)
			{
				if (s[i] == s[j] && ((j - i) < 2 || p[i + 1][j - 1]))
				{
					p[i][j] = 1;
					f[i] = min(f[i], f[j + 1] + 1);
				}
			}
		}
		int temp = f[0];
		delete[] f;
		delete_matrix(p, lenght);
		return temp;
	}
	/*maximalRectangle*/
	int maximalRectangle(vector<vector<char>> & matrix)
	{
		if (matrix.empty()) return 0;
		const int m = matrix.size();
		const int n = matrix[0].size();
		vector<int> L(n, 0);
		vector<int> H(n, 0);
		vector<int> R(n, n);

		int ret = 0;
		for (int i = 0; i < m; i++)
		{
			int left = 0, right = n;
			for (int j = 0; j < n; ++j)
			{
				if (matrix[i][j] == '1')
				{
					++H[j];
					L[j] = max(L[j], left);
				}
				else
				{
					left = j + 1;
					H[j] = 0; L[j] = 0; R[j] = n;
				}
				//cout << "  L:  " << L[j];
			}
			//cout << endl;
			for (int j = n - 1; j >= 0; --j)
			{
				if (matrix[i][j] == '1')
				{
					R[j] = min(R[j], right);
					ret = max(ret, H[j] * (R[j] - L[j]));
				}
				else
				{
					right = j;
				}
				//cout << "  R:" << R[j]<<"   H:"<<H[j];
			}
			//cout << endl;
		}
		return ret;
	}
	/*Largest Rectangle in Histogram
	* 复杂度为O（n），超时
	*修改后，能正常提交，20ms,主要对while循环进行优化，按照v2的方法，进行跳转，而不是j--,j++
	*大体复杂度为O(n),最坏O(n^2)为递增或者递减。
	有一种复杂度为O(n)的算法，用栈，较为难懂
	*/
	int largestRectangleArea(vector<int>& height)
	{
		const int n = height.size();
		vector<int> L(n, 0);
		vector<int> R(n, n);
		//左边界
		for (int i = 1; i < n; i++)
		{
			L[i] = i;
			int j = i - 1;
			while (j >= 0 && height[j] >= height[i])
			{
				L[i] = L[j];
				j = L[j] - 1;
			}
		}
		//右边界
		for (int i = n - 1; i >= 0; i--)
		{
			int j = i + 1;
			R[i] = i;
			while (j < n && height[j] >= height[i])
			{
				R[i] = R[j];
				j = R[j] + 1;
			}
		}

		int ret = 0;
		for (size_t i = 0; i < n; i++)
		{
			ret = max(ret, (R[i] - L[i] + 1)*height[i]);
		}
		return ret;
	}
	int largestRectangleArea_v2(vector<int>& height)
	{
		int n = height.size();
		int *r = new int[n];
		int *l = new int[n];

		for (int i = 0; i < n; i++){
			l[i] = i;
			int j = i - 1;
			while (j >= 0 && height[j] >= height[i]){
				l[i] = l[j];
				j = l[j] - 1;
			}
		}

		for (int i = n - 1; i >= 0; i--){
			r[i] = i;
			int j = i + 1;
			while (j < n && height[j] >= height[i]){
				r[i] = r[j];
				j = r[j] + 1;
			}
		}

		int ans = 0;
		for (int i = 0; i<n; i++){
			int temp = height[i] * (r[i] - l[i] + 1);
			if (temp > ans)
				ans = temp;
		}

		delete[] l;
		delete[] r;
		return ans;
	}
	/*Valid Parentheses 用栈来判断括号是否匹配*/
	bool isValid(string s)
	{
		string left = "[{(";
		string right = "]})";
		stack<char> cvec;
		for (auto var : s)
		{
			if (left.find(var) != string::npos)
			{
				cvec.push(var);
			}
			else
			{
				if (cvec.empty() || cvec.top() != left[right.find(var)])
					return false;
				else
					cvec.pop();
			}
		}
		return cvec.empty();
	}
	/*Longest Valid Parentheses 用栈来记录最后一个‘）’的索引位置, 每次更新max_len*/
	int longestValidParentheses(string s)
	{
		int max_len = 0;
		int last = -1;
		stack<int> cvec;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '(')
				cvec.push(i);
			else
			{
				if (cvec.empty())
					last = i;
				else
				{
					cvec.pop();
					if (cvec.empty())
						max_len = max(max_len, i - last);
					else
						max_len = max(max_len, i - cvec.top());
				}
			}
		}
		return max_len;
	}


	/*
	递归版
	假设现在走到s的i位置，p的j位置，情况分为下列两种：
	(1)p[j+1]不是'*'。情况比较简单，只要判断当前s的i和p的j上的字符是否一样（如果有p在j上的字符是'.',也是相同），如果不同，返回false，否则，递归下一层i+1，j+1;
	(2)p[j+1]是'*'。那么此时看从s[i]开始的子串，假设s[i],s[i+1],...s[i+k]都等于p[j]那么意味着这些都有可能是合适的匹配，那么递归对于剩下的(i,j+2),(i+1,j+2),...,(i+k,j+2)都要尝试（j+2是因为跳过当前和下一个'*'字符）。
	*/
	bool isMatch(const char* s, const char *p)
	{
		if (*p == '\0') return *s == '\0';
		//p[j+1]不是'*'
		if (*(p + 1) != '*')
		{
			if (*p == *s || (*p == '.' && *s != '\0'))
				return isMatch(s + 1, p + 1);
			else
				return false;
		}
		//p[j+1]是'*'
		else
		{
			while (*p == *s || (*p == '.' && *s != '\0'))
			{
				if (isMatch(s, p + 2))
					return true;
				s++;
			}
			return isMatch(s, p + 2);
		}
	}
	bool isMatch(string s, string p)
	{
		const char *s1 = s.c_str();
		const char *p1 = p.c_str();
		if (*p1 == '\0') return *s1 == '\0';
		//p[j+1]不是'*'
		if (*(p1 + 1) != '*')
		{
			if (*p1 == *s1 || (*p1 == '.' && *s1 != '\0'))
				return isMatch(s1 + 1, p1 + 1);
			else
				return false;
		}
		//p[j+1]是'*'
		else
		{
			while (*p1 == *s1 || (*p1 == '.' && *s1 != '\0'))
			{
				if (isMatch(s, p1 + 2))
					return true;
				s1++;
			}
			return isMatch(s, p1 + 2);
		}
	}

	/*
	bool isMatch_wildcard_matching(const char *s, const char *p)
	{
	if (s == NULL || p == NULL)
	{
	return false;
	}

	int n = strlen(s);
	int m = strlen(p);
	int f[n + 1][m + 1];

	memset(f, false, sizeof(f));

	f[0][0] = true;
	for (int i = 1; i <= n; i++)
	f[i][0] = false;

	for (int i = 1; i <= m; i++)
	f[0][i] = f[0][i - 1] && p[i - 1] == '*';

	for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= m; j++) {
	if (p[j - 1] == '*') {
	f[i][j] = f[i - 1][j] || f[i][j - 1];
	}
	else if (p[j - 1] == '?') {
	f[i][j] = f[i - 1][j - 1];
	}
	else {
	f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1]);
	}
	}
	} // for

	return f[n][m];
	}
	//动态规划
	bool isMatch_wild_matching(string s, string p) {
	int pLen = p.size(), sLen = s.size(), i, j, k, cur, prev;
	if (!pLen) return sLen == 0;
	bool matched[2][sLen + 1];
	fill_n(&matched[0][0], 2 * (sLen + 1), false);

	matched[0][0] = true;
	for (i = 1; i <= pLen; ++i)
	{
	cur = i % 2, prev = 1 - cur;
	matched[cur][0] = matched[prev][0] && p[i - 1] == '*';
	if (p[i - 1] == '*') for (j = 1; j <= sLen; ++j) matched[cur][j] = matched[cur][j - 1] || matched[prev][j];
	else for (j = 1; j <= sLen; ++j)            matched[cur][j] = matched[prev][j - 1] && (p[i - 1] == '?' || p[i - 1] == s[j - 1]);
	}
	return matched[cur][sLen];
	}
	*/


	//Longest common prefix,纵向扫描，复杂度为O(n1+n2+.....nn)
	string longestCommonPrefix(vector<string> &strs)
	{
		if (strs.empty()) return "";
		for (size_t i = 0; i < strs[0].size(); i++)
		{
			for (size_t j = 0; j < strs.size(); j++)
			{
				if (strs[j][i] != strs[0][i]) return strs[0].substr(0, i);
			}
		}
		return strs[0];
	}

	//valid number ,使用自动机
	bool isNumber(string s)
	{
		char fsm[10][128];
		memset(fsm, 10, sizeof(fsm));
		for (char i = '0'; i <= '9'; i++)
		{
			fsm[0][i] = 1;
			fsm[1][i] = 1;
			fsm[2][i] = 3;
			fsm[3][i] = 3;
			fsm[5][i] = 3;
			fsm[6][i] = 1;
			fsm[7][i] = 8;
			fsm[8][i] = 8;
			fsm[2][i] = 8;
			fsm[9][i] = 8;
		}
		fsm[0][' '] = 0;
		fsm[1][' '] = 4;
		fsm[3][' '] = 4;
		fsm[4][' '] = 4;
		fsm[8][' '] = 4;
		fsm[1]['e'] = 2;
		fsm[3]['e'] = 7;
		fsm[1]['.'] = 3;
		fsm[0]['.'] = 5;
		fsm[0]['-'] = 6;
		fsm[0]['+'] = 6;
		fsm[6]['.'] = 5;
		fsm[7]['+'] = 9;
		fsm[7]['-'] = 9;
		fsm[2]['+'] = 9;
		fsm[2]['-'] = 9;
		int state = 0;
		for (auto c : s)
		{
			state = fsm[state][c];
			if (state > 9)
			{
				return false;
			}
		}
		if (state == 1 || state == 3 || state == 4 || state == 8)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//valid number
	bool isNumber_FSM(const char *s)
	{
		enum InputType
		{
			INVALID, // 0
			SPACE, // 1 空格
			SIGN, // 2 正负号
			DIGIT, // 3  数字
			DOT, // 4  点号
			EXPONENT, // 5  指数
			NUM_INPUTS // 6 
		};
		const int transitionTable[][NUM_INPUTS] =
		{
			-1, 0, 3, 1, 2, -1, // next states for state 0
			-1, 8, -1, 1, 4, 5, // next states for state 1
			-1, -1, -1, 4, -1, -1, // next states for state 2
			-1, -1, -1, 1, 2, -1, // next states for state 3
			-1, 8, -1, 4, -1, 5, // next states for state 4
			-1, -1, 6, 7, -1, -1, // next states for state 5
			-1, -1, -1, 7, -1, -1, // next states for state 6
			-1, 8, -1, 7, -1, -1, // next states for state 7
			-1, 8, -1, -1, -1, -1, // next states for state 8
		};
		int state = 0;
		for (; *s != '\0'; ++s)
		{
			InputType inputType = INVALID;
			if (isspace(*s))
				inputType = SPACE;
			else if (*s == '+' || *s == '-')
				inputType = SIGN;
			else if (isdigit(*s))
				inputType = DIGIT;
			else if (*s == '.')
				inputType = DOT;
			else if (*s == 'e' || *s == 'E')
				inputType = EXPONENT;
			// Get next state from current state and input symbol
			state = transitionTable[state][inputType];
			// Invalid input
			if (state == -1) return false;
		}
		// If the current state belongs to one of the accepting (final) states,
		// then the number is valid
		return state == 1 || state == 4 || state == 7 || state == 8;
	}

	/*valid number，使用 strtod库函数*/
	bool isNumber_strtod(string s)
	{
		const char *cstr = s.c_str();
		char *endptr;
		strtod(cstr, &endptr);
		if (endptr == cstr) return false;
		for (; *endptr; ++endptr)
		if (!isspace(*endptr)) return false;
		return true;
	}
	/*
	valid number，使用正则表达式匹配
	leetcode不能识别regex
	*/
	bool isNumber_regex(string s) {
		//这里要去除首和末的空白符
		//s = s.trim();
		s = trim(s);
		regex pattern("[+-]?(([0-9]*\\.?[0-9]+)|([0-9]+\\.?[0-9]*))([eE][+-]?[0-9]+)?");
		bool res = regex_match(s, pattern);
		if (res) return true;
		else return false;
	}
	/*
	纯模拟：
	基本字符:I V X L C D M
	相应的阿拉伯数字表示为 1 5 10 50 100 500 1000
	另外:
	1.相同的数字连写，所表示的数等于这些数字相加得到的数，如：Ⅲ = 3；
	2.小的数字在大的数字的右边，所表示的数等于这些数字相加得到的数， 如：Ⅷ = 8；Ⅻ = 12；
	3.小的数字，（限于Ⅰ、X 和C）在大的数字的左边，所表示的数等于大数减小数得到的数，如：Ⅳ= 4；Ⅸ= 9；
	4.正常使用时，连写的数字重复不得超过三次。（表盘上的四点钟“IIII”例外）
	5.在一个数的上面画一条横线，表示这个数扩大1000倍。
	*/
	string intToRoman(int num)
	{
		const int radix[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
		const string symbol[] = { "M", "CM", "D", "CD", "C", "XC",
			"L", "XL", "X", "IX", "V", "IV", "I" };
		string roman;
		for (size_t i = 0; num > 0; i++)
		{
			int count = num / radix[i];
			num = num % radix[i];
			for (; count > 0; --count)
				roman += symbol[i];
		}
		return roman;
	}
	/*
	前往后扫描，用一个临时变量记录分段数字。
	如果当前比前一个大，说明这一段的值应该是当前这个值减去上一个值。
	*/
	int romanToInt(string s)
	{
		map<char, int> roman = { { 'I', 1 }, { 'V', 5 }, { 'X', 10 }, { 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };
		int sum = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (i>0 && roman[s[i]] > roman[s[i - 1]])
				sum += (roman[s[i]] - 2 * roman[s[i - 1]]); /*前一位的值被计算，需要减去*/
			else
				sum += roman[s[i]];
		}
		return sum;
	}

	/*
	模拟
	题意是n=1时输出字符串1；n=2时，数上次字符串中的数值个数，因为上次字符串有1个1，所以输出11；
	n=3时，由于上次字符是11，有2个1，所以输出21；n=4时，由于上次字符串是21，有1个2和1个1，所以输出1211。依次类推。
	*/
	string countAndSay(int n)
	{
		string s = "1";
		while (--n)
			s = getNext(s);
		return s;
	}
	string getNext(const string &s)
	{
		std::stringstream ss;
		for (auto i = s.begin(); i != s.end();)
		{
			auto j = find_if(i, s.end(), bind1st(not_equal_to<char>(), *i));
			ss << distance(i, j) << *i;
			i = j;
		}
		return ss.str();
	}
	/*
	Anagrams
	problem:Given an array of strings, return all groups of strings that are anagrams.
	analysis:单词里的字母的种类和数目没有改变，只是改变了字母的排列顺序。 因此，将几个单词按照字母顺序排序后，若它们相等，则它们属于同一组 anagrams 。
	*/
	vector<string> anagrams(vector<string> &strs)
	{
		unordered_map<string, vector<string>> group;
		for (const auto &s : strs)
		{
			string key = s;
			sort(key.begin(), key.end());
			group[key].push_back(s);
		}
		vector<string> result;
		for (auto it = group.cbegin(); it != group.cend(); it++)
		{
			if (it->second.size() > 1)
				result.insert(result.end(), it->second.begin(), it->second.end());
		}
		return result;
	}
	/*Group Anagrams*/
	vector<vector<string>> groupAnagrams(vector<string>& strs)
	{
		unordered_map<string, vector<string>> group;
		for (const auto &s : strs)
		{
			string key = s;
			sort(key.begin(), key.end());
			group[key].push_back(s);
		}
		vector<vector<string>> result;
		for (auto it = group.cbegin(); it != group.cend(); it++)
		{
			vector<string> temp = it->second;
			sort(temp.begin(), temp.end());
			result.push_back(temp);
		}
		return result;
	}
	/*valid anagram , 判断两个字符串是不是anagram*/
	bool isAnagram(string s, string t)
	{
		sort(s.begin(), s.end());
		sort(t.begin(), t.end());
		if (s == t) return true;
		else return false;
	}
	/*simplify path*/
	string simplifyPath(string path)
	{
		vector<string> dirs; // 当做栈
		for (auto i = path.begin(); i != path.end();)
		{
			++i;
			auto j = find(i, path.end(), '/');
			auto dir = string(i, j);
			if (!dir.empty() && dir != ".")
			{
				// 当有连续 '///' 时， dir 为空
				if (dir == "..")
				{
					if (!dirs.empty())
						dirs.pop_back();  /*pop_back位删除最后一个元素*/
				}
				else
					dirs.push_back(dir);
			}
			i = j;
		}
		//stringstream 用来构造格式化字符串
		stringstream out;
		if (dirs.empty())
		{
			out << "/";
		}
		else
		{
			for (auto dir : dirs)
				out << '/' << dir;
		}
		return out.str();
	}
	int lengthOfLastWord(string s)
	{
		trim(s);
		vector<string> result = split(s, " ");
		if (result.size() == 0) return 0;
		else return result[result.size() - 1].size();
	}
	int lengthOfLastWord_v2(string s)
	{
		int len = s.length();
		int count = 0;
		for (int i = len - 1; i >= 0; i--)
		{
			if (s[i] == ' ' && count) break;
			if (s[i] != ' ') count++;
		}
		return count;
	}
	int evalRPN(vector<string>& tokens)
	{
		stack<int> number_stack;
		int a, b, res;
		for (size_t i = 0; i < tokens.size(); i++)
		{
			string temp = tokens[i];
			if (temp.size() == 1 && (temp == "+" || temp == "-" || temp == "/" || temp == "*"))
			{
				a = number_stack.top();
				number_stack.pop();
				b = number_stack.top();
				number_stack.pop();
				if (temp == "+") res = a + b;
				else if (temp == "-") res = b - a;
				else if (temp == "/") res = b / a;
				else res = a*b;
				number_stack.push(res);

			}
			else
			{
				number_stack.push(atoi(temp.c_str()));
			}
		}
		return number_stack.top();
	}
	/*Binary Tree Preorder Traversal , 递归版本*/
	vector<int> preorderTraversal(TreeNode *root)
	{
		vector<int> result;
		if (root == nullptr) return result;
		result.push_back(root->val);
		vector<int> left = preorderTraversal(root->left);
		result.insert(result.end(), left.begin(), left.end());
		vector<int> right = preorderTraversal(root->right);
		result.insert(result.end(), right.begin(), right.end());
		return result;
	}
	/*非递归，用栈*/
	vector<int> preorderTraversal_v2(TreeNode *root)
	{
		stack<TreeNode*> stack_tree;
		vector<int> result;
		if (root == nullptr)
			return result;
		stack_tree.push(root);
		while (!stack_tree.empty())
		{
			TreeNode * ptr_tree = stack_tree.top();
			result.push_back(ptr_tree->val);
			stack_tree.pop();
			if (ptr_tree->right != nullptr)
				stack_tree.push(ptr_tree->right);
			if (ptr_tree->left != nullptr)
				stack_tree.push(ptr_tree->left);
		}
		return result;
	}
	// Morris 先序遍历，时间复杂度 O(n)，空间复杂度 O(1)
	vector<int> preorderTraversal_v3(TreeNode *root)
	{
		vector<int> result;
		TreeNode *cur, *prev;
		cur = root;
		while (cur != nullptr)
		{
			if (cur->left == nullptr)
			{
				result.push_back(cur->val);
				prev = cur; /* cur 刚刚被访问过 */
				cur = cur->right;
			}
			else
			{
				/* 查找前驱 */
				TreeNode *node = cur->left;
				while (node->right != nullptr && node->right != cur)
					node = node->right;
				if (node->right == nullptr)   /* 还没线索化，则建立线索 */
				{
					result.push_back(cur->val); /* 仅这一行的位置与中序不同 */
					node->right = cur;
					prev = cur; /* cur 刚刚被访问过 */
					cur = cur->left;
				}
				else     /* 已经线索化，则删除线索 */
				{
					node->right = nullptr;
					/* prev = cur; 不能有这句， cur 已经被访问 */
					cur = cur->right;
				}
			}
		}
		return result;
	}
	/*inorderTraversal，栈 用标志位来记录是否访问过*/
	vector<int> inorderTraversal(TreeNode* root)
	{
		typedef struct node_flag
		{
			TreeNode *node;
			int flag = 0;  //标记位
			node_flag(TreeNode * val) :node(val){}
		};
		stack<node_flag> stack_tree;
		vector<int> result;
		if (root == nullptr)
			return result;
		node_flag flag_root(root);
		stack_tree.push(flag_root);

		while (!stack_tree.empty())
		{
			node_flag  ptr_tree = stack_tree.top();
			if (ptr_tree.flag ==1)	
				result.push_back(ptr_tree.node->val);
			stack_tree.pop();
			
			if (ptr_tree.node->right != nullptr && ptr_tree.flag == 0)
			{
				node_flag flag_right(ptr_tree.node->right);
				stack_tree.push(flag_right);
			}
			
			//left_flag来保存标记
			int left_flag = ptr_tree.flag;
			if (ptr_tree.flag == 0)
			{
				ptr_tree.flag = 1;
				stack_tree.push(ptr_tree);
			}

			if (ptr_tree.node->left != nullptr && left_flag == 0)
			{
				node_flag flag_left(ptr_tree.node->left);
				stack_tree.push(flag_left);
			}
			
		}
		return result;
	}
	vector<int> inorderTraversal_v2(TreeNode *root) {
		vector<int> result;
		const TreeNode *p = root;
		stack<const TreeNode *> s;
		while (!s.empty() || p != nullptr) {
			if (p != nullptr) {
				s.push(p);
				p = p->left;
			}
			else {
				p = s.top();
				s.pop();
				result.push_back(p->val);
				p = p->right;
			}
		}
		return result;
	}
	// Morris 中序遍历，时间复杂度 O(n)，空间复杂度 O(1)
	vector<int> inorderTraversal_v3(TreeNode *root)
	{
		vector<int> result;
		TreeNode *cur, *prev;
		cur = root;
		while (cur != nullptr)
		{
			if (cur->left == nullptr)
			{
				result.push_back(cur->val);
				prev = cur;
				cur = cur->right;
			}
			else
			{
				/* 查找前驱 */
				TreeNode *node = cur->left;
				while (node->right != nullptr && node->right != cur)
					node = node->right;
				if (node->right == nullptr)   /* 还没线索化，则建立线索 */
				{
					node->right = cur;
					/* prev = cur; 不能有这句， cur 还没有被访问 */
					cur = cur->left;
				}
				else     /* 已经线索化，则访问节点，并删除线索 */
				{
					result.push_back(cur->val);
					node->right = nullptr;
					prev = cur;
					cur = cur->right;
				}
			}
		}
		return result;
	}
	/*用栈，用flag来记录是否被访问*/
	vector<int> postorderTraversal(TreeNode* root)
	{
		typedef struct node_flag
		{
			TreeNode *node;
			int flag = 0; //记录是否被访问
			node_flag(TreeNode * val) :node(val){}
		};
		stack<node_flag> stack_tree;
		vector<int> result;
		if (root == nullptr)
			return result;
		node_flag flag_root(root);
		stack_tree.push(flag_root);

		while (!stack_tree.empty())
		{
			node_flag  ptr_tree = stack_tree.top();
			if (ptr_tree.flag == 1)
				result.push_back(ptr_tree.node->val);
			stack_tree.pop();

			int left_flag = ptr_tree.flag;
			if (ptr_tree.flag == 0)
			{
				ptr_tree.flag = 1;
				stack_tree.push(ptr_tree);
			}

			if (ptr_tree.node->right != nullptr && left_flag == 0)
			{
				node_flag flag_right(ptr_tree.node->right);
				stack_tree.push(flag_right);
			}


			if (ptr_tree.node->left != nullptr && left_flag == 0)
			{
				node_flag flag_left(ptr_tree.node->left);
				stack_tree.push(flag_left);
			}

		}
		return result;
	}
	// Morris 后序遍历，时间复杂度 O(n)，空间复杂度 O(1)
	vector<int> postorderTraversal_v2(TreeNode *root)
	{
		vector<int> result;
		TreeNode dummy(-1);
		TreeNode *cur, *prev = nullptr;
		std::function < void(const TreeNode*)> visit =
			[&result](const TreeNode *node)
		{
			result.push_back(node->val);
		};
		dummy.left = root;
		cur = &dummy;
		while (cur != nullptr)
		{
			if (cur->left == nullptr)
			{
				prev = cur; /* 必须要有 */
				cur = cur->right;
			}
			else
			{
				TreeNode *node = cur->left;
				while (node->right != nullptr && node->right != cur)
					node = node->right;
				if (node->right == nullptr)   /* 还没线索化，则建立线索 */
				{
					node->right = cur;
					prev = cur; /* 必须要有 */
					cur = cur->left;
				}
				else     /* 已经线索化，则访问节点，并删除线索 */
				{
					visit_reverse(cur->left, prev, visit);
					prev->right = nullptr;
					prev = cur; /* 必须要有 */
					cur = cur->right;
				}
			}
		}
		return result;
	}
	/*Binary Tree Level Order Traversal*/
	vector<vector<int>> levelOrder(TreeNode* root)
	{
		typedef struct level_tree
		{
			TreeNode *node;
			int level;
			level_tree(TreeNode *node1, int level1) :node(node1), level(level1){}
		}level_tree;
		vector<vector<int>> result;
		queue<level_tree> q;
		if (root == nullptr) return result;
		level_tree tree_node(root, 0);
		q.push(tree_node);
		int level_flag = 0;
		vector<int> ivec;
		while (!q.empty())
		{
			level_tree temp_node = q.front();
			q.pop();
			if (temp_node.level != level_flag)
			{
				result.push_back(ivec);
				vector<int> tep;
				swap(tep, ivec);
				ivec.clear();
				level_flag += 1;
			}
			ivec.push_back(temp_node.node->val);
			if (temp_node.node->left != nullptr)
			{
				level_tree left_node(temp_node.node->left, temp_node.level + 1);
				q.push(left_node);
			}
			if (temp_node.node->right != nullptr)
			{
				level_tree left_node(temp_node.node->right, temp_node.level + 1);
				q.push(left_node);
			}
		}
		if (!ivec.empty())
			result.push_back(ivec);
		//下面一行用于level order 2题
		//reverse(result.begin(), result.end());
		return result;
	}
	// 递归版，时间复杂度 O(n)，空间复杂度 O(n)
	vector<vector<int> > levelOrder_v2(TreeNode *root)
	{
		vector<vector<int>> result;
		traverse(root, 1, result);
		return result;
	}
	void traverse(TreeNode *root, size_t level, vector<vector<int>> &result)
	{
		if (!root) return;
		if (level > result.size())
			result.push_back(vector<int>());
		result[level - 1].push_back(root->val);
		traverse(root->left, level + 1, result);
		traverse(root->right, level + 1, result);
	}
	/*Binary Tree Zigzag Level Order Traversal，递归*/
	vector<vector<int>> zigzagLevelOrder(TreeNode* root)
	{
		vector<vector<int>> result;
		zigzag_traverse(root, 0, result);
		return result;
	}
	void zigzag_traverse(TreeNode *root, size_t level, vector<vector<int>> &result)
	{
		if (!root) return;
		if (level+1 > result.size())
			result.push_back(vector<int>());
		if (level % 2 == 0) result[level].push_back(root->val);
		else result[level].insert(result[level].begin(), root->val);

		zigzag_traverse(root->left, level + 1, result);
		zigzag_traverse(root->right, level + 1, result);
	}
	/*Recover Binary Search Tree*/
	void recoverTree(TreeNode* root)
	{
		vector<TreeNode*> res = recoverTree_inorder(root);
		TreeNode *firstEle = nullptr;
		TreeNode *secondEle = nullptr;
		int lenght = res.size();
		for (size_t i = 0; i < lenght; i++)
		{
			if ((i>0 && (res[i - 1]>res[i])) || ((i<lenght - 1) && (res[i]>res[i+1])))
			if (firstEle == nullptr) firstEle = res[i];
			else { secondEle = res[i]; break; }
		}
		swap(firstEle->val, secondEle->val);
	}
	vector<TreeNode*> recoverTree_inorder(TreeNode *root) {
		vector<TreeNode*> result;
		TreeNode *p = root;
		stack<TreeNode *> s;
		while (!s.empty() || p != nullptr) {
			if (p != nullptr) {
				s.push(p);
				p = p->left;
			}
			else {
				p = s.top();
				s.pop();
				TreeNode * temp = p;
				result.push_back(temp);
				p = p->right;
			}
		}
		return result;
	}
	/*内部类，Recover Binary Search Tree*/
	class recoverTree_sol
	{
	public:
		TreeNode *p, *q;
		TreeNode *prev;
		void recoverTree(TreeNode *root)
		{
			p = q = prev = NULL;
			inorder(root);
			swap(p->val, q->val);
		}
		void inorder(TreeNode *root)
		{
			if (root->left)inorder(root->left);
			if (prev != NULL && (prev->val>root->val))
			{
				if (p == NULL)p = prev;
				q = root;
			}
			prev = root;
			if (root->right)inorder(root->right);
		}
	};
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		if (!p && !q) return true; // 终止条件
		if (!p || !q) return false; // 剪枝
		return p->val == q->val // 三方合并
			&& isSameTree(p->left, q->left)
			&& isSameTree(p->right, q->right);
	}
	bool isSymmetric(TreeNode *root) {
		return root ? isSymmetric(root->left, root->right) : true;
	}
	bool isSymmetric(TreeNode *left, TreeNode *right) {
		if (!left && !right) return true; // 终止条件
		if (!left || !right) return false; // 终止条件
		return left->val == right->val // 三方合并
			&& isSymmetric(left->left, right->right)
			&& isSymmetric(left->right, right->left);
	}
	/*balanced binary tree，递归*/
	bool isBalanced(TreeNode* root)
	{
		return balanceHeight(root) >= 0;
	}
	int balanceHeight(TreeNode *root)
	{
		if (root == nullptr) return 0;
		int left = balanceHeight(root->left);
		int right = balanceHeight(root->right);
		if (left < 0 || right <0 || abs(left - right)>1) return -1;
		return max(left, right) + 1;
	}
	/*flatten binary tree to linked list*/
	void flatten(TreeNode* root)
	{
		if (root == nullptr) return;
		vector<TreeNode*> node_vec;
		flatten_preorder(root, node_vec);
		size_t length = node_vec.size();
		for (size_t i = 1; i < length; i++)
		{
			node_vec[i-1]->right = node_vec[i];
			node_vec[i - 1]->left = nullptr;
		}
		node_vec[length - 1]->right = nullptr;
		node_vec[length - 1]->left = nullptr;
	}
	void flatten_preorder(TreeNode* root, vector<TreeNode*> &res)
	{
		if (root == nullptr) return;
		res.push_back(root);
		flatten_preorder(root->left,res);
		flatten_preorder(root->right,res);
	}
	void connect(TreeLinkNode *root)
	{
		if (root == nullptr) return;
		TreeLinkNode dump(-1);
		for (TreeLinkNode *pre=&dump,*cur=root;cur; cur=cur->next)
		{
			if (cur->left != nullptr)
			{
				pre->next = cur->left;
				pre = pre->next;
			}
			if (cur->right != nullptr)
			{
				pre->next = cur->right;
				pre = pre->next;
			}
		}
		connect(dump.next);
	}

};
/*陈硕，多路归并排序*/
File mergeN(const std::vector<File>& files)
{
	File output;
	std::vector<Input> inputs;

	for (size_t i = 0; i < files.size(); ++i)
	{
		Input input(&files[i]);
		if (input.next())
		{
			inputs.push_back(input);
		}
	}

	std::make_heap(inputs.begin(), inputs.end());
	while (!inputs.empty())
	{
		std::pop_heap(inputs.begin(), inputs.end());
		output.push_back(inputs.back().value);

		if (inputs.back().next())
		{
			std::push_heap(inputs.begin(), inputs.end());
		}
		else
		{
			inputs.pop_back();
		}
	}

	return output;
}
void mergeN_test()
{
	//生成数据
	const int kFiles = 32;
	std::vector<File> files(kFiles);
	for (int i = 0; i < kFiles; ++i)
	{
		File file(rand() % 1000);
		std::generate(file.begin(), file.end(), &rand);
		std::sort(file.begin(), file.end());
		files[i].swap(file);
	}
	//多路归并排序
	File output = mergeN(files);

	//输出排序结果
	cout << output.size() << endl;
	std::copy(output.begin(), output.end(),
		std::ostream_iterator<Record>(std::cout, "\n"));
}
void test_init()
{
	int *pt1 = new int[10];
	int *pt2 = new int[10]();

	delete[] pt1;
	delete[] pt2;
}

/*测试std::next的代码*/
void test_next()
{
	std::list<int> mylist;
	for (int i = 0; i < 10; i++) mylist.push_back(i * 10);

	std::cout << "mylist:";
	std::for_each(mylist.begin(),
		std::next(mylist.begin(), 5),
		[](int x)
	{
		std::cout << ' ' << x;
	});

	std::cout << '\n';
}
void example(char acWelcome[])
{
	printf("%d", sizeof(acWelcome));
	return;
}
//百度笔试，timo毒蘑菇问题
void get_line_count(int n, int m)
{
	int *matrix = new int[n*m];
	//先计算全部路线
	for (int i = 0; i < n*m; i++)
	{
		matrix[i] = 1;
	}
	for (size_t i = 1; i < n; i++)
	{
		for (size_t j = 1; j < m; j++)
		{
			matrix[i*m + j] = matrix[i*m + j - 1] + matrix[(i - 1)*m + j];
		}
	}
	cout << "line counts:" << matrix[n*m - 1] << endl;

	//下面计算安全路线
	vector<pair<int, int>> point_vec;
	for (int i = 0; i < n*m; i++)
	{
		matrix[i] = 1;
	}
	for (size_t i = 0; i < point_vec.size(); i++)
	{
		matrix[(point_vec[i].first - 1)*m + point_vec[i].second] = 0;
	}
	for (size_t i = 1; i < n; i++)
	{
		for (size_t j = 1; j < m; j++)
		{
			if (matrix[i*m + j] != 0)
				matrix[i*m + j] = matrix[i*m + j - 1] + matrix[(i - 1)*m + j];
		}
	}
	cout << "safe counts:" << matrix[n*m - 1] << endl;

	delete[] matrix;
}


# if 1
int main()
{
	TreeNode root(2);
	TreeNode left(1);
	TreeNode right(3);
	//left.left = &right;
	root.right = &left;


	Solution sol;
	vector<int> res = sol.inorderTraversal_v2(&root);
	for each (auto var in res)
	{
		cout << var << " ";
	}
		sol.flatten(&root);
		//vector<int> res = sol.inorderTraversal_v2(&root);
		for each (auto var in res)
		{
			cout << var << " ";
		}
	system("pause");
	return 0;
}
#endif
