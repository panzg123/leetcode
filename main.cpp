#include"header.h"

using namespace std;
class Solution
{
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
		for (auto a = num.begin(); a !=  prev(num.end(),2); a++)
		{
			auto b = next(a);
			auto c = prev(num.end());
			while (b<c)
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
	/// leetcode , fourSum,��unordered_multimap,��ʱ
	vector<vector<int>> fourSum(vector<int> &num, int target)
	{
		vector<vector<int>> result;
		if (num.size() < 4)
			return result;
		sort(num.begin(), num.end());
		unordered_multimap<int, pair<int, int>> cache;
		for (size_t i = 0; i < num.size(); ++i)
		{
			for (size_t j = i+1; j < num.size(); ++j)
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

				if (a!=c&&a!=d&&b!=c&&b!=d)
				{
					vector < int > vec= {num[a],num[b],num[c],num[d]};
					sort(vec.begin(), vec.end());
					result.push_back(vec);
				} 
			}
		}
		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;

	}
	//leetcode,4sum,��unodered_map������ʱ
	vector<vector<int>> fourSum_v2(vector<int> &num, int target)
	{
		vector<vector<int>> result;
		if (num.size() < 4) return result;
		sort(num.begin(), num.end());
		unordered_map<int, vector<pair<int, int> > > cache;
		for (size_t a = 0; a < num.size(); ++a) {
			for (size_t b = a + 1; b < num.size(); ++b) {
				cache[num[a] + num[b]].push_back(pair<int, int>(a, b));
			}
		}
		for (int c = 0; c < num.size(); ++c) {
			for (size_t d = c + 1; d < num.size(); ++d) {
				const int key = target - num[c] - num[d];
				if (cache.find(key) == cache.end()) continue;
				const auto& vec = cache[key];
				for (size_t k = 0; k < vec.size(); ++k) {
					if (c <= vec[k].second)
						continue; // ���ص�
					result.push_back({ num[vec[k].first],
						num[vec[k].second], num[c], num[d] });
				}
			}
		}
		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;
	}
	//leetcode,remove element
	int removeElement(vector<int> &nums,int val)
	{
		int index = 0;
		vector<int> vec;
		for (size_t i = 0; i < nums.size(); i++)
		{
			if (nums[i]!=val)
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
	void nextPermutation(vector<int> &nums) {
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
	/*permutation_sequence �����ƽⷨ ��ʱ*/
	string permutation_sequence(const int n, const int k)
	{
		string str(n,'0');
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
	/*permutation sequence ��������ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(1) */
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

		//ɨ�����
		for (int i = 1; i < n; i++)
		{
			if (A[i-1]>left_flag[i-1])
			{
				left_flag[i] = A[i - 1];
			}
			else
			{
				left_flag[i] = left_flag[i - 1];
			}
		}
		//ɨ���ұ�
		for (int i = n-2; i >=0; i--)
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
			result += (compare>0 ? compare:0);
		}

		delete[] left_flag;
		delete[] right_flag;
		return result;
	}
	/*trapping train water v2*/
	int trap(vector<int> &height)
	{
		int result=0;
		int n = height.size();
		int *left_flag = new int[n];
		int *right_flag = new  int[n];
		memset(left_flag, INT_MAX, n*sizeof(int));
		memset(right_flag, INT_MAX, n* sizeof(int));
		left_flag[0] = 0;
		right_flag[n - 1] = 0;

		//ɨ�����
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
		//ɨ���ұ�
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
	ʱ�临�Ӷ� O(n^2)���ռ临�Ӷ� O(1)
	*/
	void rotate(vector<vector<int>> &matrix)
	{
		int n = matrix.size();
		//ת�þ���
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < i; j++)
			{
				swap(matrix[i][j], matrix[j][i]);
			}
		}
		//���ҷ�ת
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n/2; j++)
			{
				swap(matrix[i][j], matrix[i][n-1-j]);
			}
		}
	}
	/*climbing stairs*/
	int climbStairs(int n)
	{
		int pre1 = 1, pre2 = 1;
		int cur = 0;
		if (n==0)
		{
			return pre1;
		}
		if (n==1)
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
	/*�ռ临�Ӷ�ΪO(m+n)*/
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
				if (matrix[i][j]==0)
				{
					row_flags[i] = colum_flags[j] = 0;
				}
			}
		}
		for (size_t i = 0; i < rows; i++)
		{
			if (row_flags[i]==0)
			{
				for (size_t j = 0; j < colums; j++)
				{
					matrix[i][j] = 0;
				}
			}
		}
		for (size_t i = 0; i < colums; i++)
		{
			if (colum_flags[i]==0)
			{
				for (size_t j = 0; j < rows; j++)
				{
					matrix[j][i] = 0;
				}
			}
		}
	}
	/*
	*�ռ临�Ӷ�ΪO��1��
	*���õ�һ�к͵�һ�У��ȱ�ǵ�һ�к͵�һ���Ƿ���0Ԫ�أ�Ȼ��������������0�ͽ���Ԫ�ص����е�һ��Ԫ�ر��Ϊ0.
	*/
	void setZeros_v2(vector<vector<int>> &matrix)
	{
		int rows = matrix.size();
		int colums = matrix[0].size();
		int first_rows_have_zero = 0,first_colum_have_zero=0;
		//��ǵ�һ���Ƿ���0Ԫ��
		for (size_t i = 0; i < colums; i++)
		{
			if (matrix[0][i]==0)
			{
				first_rows_have_zero = 1;
				break;
			}
		}
		//��ǵ�һ���Ƿ���0Ԫ��
		for (size_t i = 0; i < rows; i++)
		{
			if (matrix[i][0]==0)
			{
				first_colum_have_zero = 1;
				break;
			}
		}
		//���õ�һ�к͵�һ�У������0Ԫ�ؾͽ���Ԫ�ص����е�һ��Ԫ����0
		for (size_t i = 1; i < rows; i++)
		{
			for (size_t j = 1; j < colums; j++)
			{
				if (matrix[i][j]==0)
				{
					matrix[0][j] = 0;
					matrix[i][0] = 0;
				}
			}
		}
		//�����������һ�е�һ�е�Ԫ��Ϊ0�����Ԫ��ӦΪ0
		for (size_t i = 1; i < rows; i++)
		{
			for (size_t j = 1; j < colums; j++)
			{
				if (matrix[0][j]==0||matrix[i][0]==0)
				{
					matrix[i][j] = 0;
				}
			}
		}
		//���۵�һ���Ƿ�0
		if (first_colum_have_zero)
		{
			for (size_t i = 0; i < rows; i++)
			{
				matrix[i][0] = 0;
			}
		}
		//���۵�һ���Ƿ�0
		if (first_rows_have_zero)
		{
			for (size_t i = 0; i < colums; i++)
			{
				matrix[0][i] = 0;
			}
		}
	}
	/*���ⲻ��*/
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
	{
		int total = 0;
		int j = -1;
		for (int i = 0, sum = 0; i < gas.size(); ++i) {
			sum += gas[i] - cost[i];
			total += gas[i] - cost[i];
			if (sum < 0) {
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
		vector<int> candy(number,1);
		
		int inc=2;
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
		for (int i = number-2; i >= 0; i--)
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
	/*��ʹ�ö���Ŀռ�*/
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
		ListNode *result_header=&val;
		for (ListNode *ptr1 = l1, *ptr2 = l2;
			ptr1 != nullptr || ptr2 != nullptr;
			ptr1=(ptr1==nullptr?nullptr:ptr1->next),
			ptr2=(ptr2==nullptr?nullptr:ptr2->next),
			result_header=result_header->next)
		{
			const int val_a = ptr1==nullptr?0:ptr1->val;
			const int val_b = ptr2==nullptr?0:ptr2->val;
			const int value = (val_a + val_b + carry) % 10;
			carry = (val_a + val_b + carry) / 10;

			result_header->next = new ListNode(value);
		}
		if (carry>0)
		{
			result_header->next = new ListNode(carry);
		}
		return val.next;
	}
	ListNode *addTwoNumbers2(ListNode *l1, ListNode *l2) {
		ListNode dummy(-1); // ͷ�ڵ�
		int carry = 0;
		ListNode *prev = &dummy;
		for (ListNode *pa = l1, *pb = l2;
			pa != nullptr || pb != nullptr;
			pa = pa == nullptr ? nullptr : pa->next,
			pb = pb == nullptr ? nullptr : pb->next,
			prev = prev->next) {
			const int ai = pa == nullptr ? 0 : pa->val;
			const int bi = pb == nullptr ? 0 : pb->val;
			const int value = (ai + bi + carry) % 10;
			carry = (ai + bi + carry) / 10;
			prev->next = new ListNode(value); // β�巨
		}
		if (carry > 0)
			prev->next = new ListNode(carry);
		return dummy.next;
	}
	/*Reverse Linked List II*/
	ListNode* reverseBetween(ListNode* head, int m, int n)
	{
		if (n==m)
		{
			return head;
		}
		ListNode *myhead = new ListNode(-1);
		myhead->next = head;
		ListNode *pre = myhead;
		int count = 1;
		while (count!=m)
		{
			pre = pre->next;
			count++;
		}
		ListNode *first = pre->next;
		ListNode *second = first->next;
		while (count<n)
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
		ListNode *tail_less=my_header_less;
		ListNode *tail_more=my_header_more;
		while (head!=nullptr)
		{
			temp = head->next;
			if (head->val<x)
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
		while (p->next)   // �󳤶�
		{
			len++;
			p = p->next;
		}
		k = len - k % len;
		p->next = head; // ��β����
		for (int step = 0; step < k; step++)
		{
			p = p->next; //����������
		}
		head = p->next; // �µ��׽ڵ�
		p->next = nullptr; // �Ͽ���
		return head;
	}


private:
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
	// seq ���ź����ǵ�һ������
	template<typename Sequence>
	Sequence kth_permutation(const Sequence &seq, int k)
	{
		const int n = seq.size();
		Sequence S(seq);
		Sequence result;
		int base = factorial(n - 1);
		--k; // ���б���� 0 ��ʼ
		for (int i = n - 1; i > 0; k %= base, base /= i, --i)
		{
			auto a = next(S.begin(), k / base);
			result.push_back(*a);
			S.erase(a);
		}
		result.push_back(S[0]); // ���һ��
		return result;
	}
};


/*����std::next�Ĵ���*/
void test_next()
{
	std::list<int> mylist;
	for (int i = 0; i<10; i++) mylist.push_back(i * 10);

	std::cout << "mylist:";
	std::for_each(mylist.begin(),
		std::next(mylist.begin(), 5),
		[](int x) {std::cout << ' ' << x; });

	std::cout << '\n';
}

int main()
{
	ListNode *l1 = new ListNode(1);
	ListNode *l2 = new ListNode(2);
	ListNode *l3 = new ListNode(3);
	ListNode *l4 = new ListNode(4);
	ListNode *l5 = new ListNode(5);
	//ListNode *l6 = new ListNode(2);
	l1->next = l2;
	l2->next = l3;
	l3->next = l4;
	l4->next = l5;
	//l5->next = l6;

	ListNode * ll2 = nullptr;

	Solution solution;
	ListNode* res = solution.rotateRight(ll2,0);
	for (ListNode *ptr = res; ptr!=nullptr; ptr=ptr->next)
	{
		cout << " " << ptr->val;
	}

	system("pause");
		return 0;
}