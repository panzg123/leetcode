#include"header.h"
using namespace std;
class Solution
{
public:
	/*merge sorted array
	时间复杂度 O(m+n)，空间复杂度 O(1)*/
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		int ia = m - 1, ib = n - 1, icur = m + n - 1;
		while (ia >= 0 && ib >= 0)
		{
			nums1[icur--] = (nums1[ia] > nums2[ib]) ? nums1[ia--] : nums2[ib--];
		}
		while (ib >= 0)
			nums1[icur--] = nums2[ib--];
	}
	/*Merge Two Sorted Lists 时间复杂度 O(min(m,n))，空间复杂度 O(1)*/
	ListNode* mergeTwoLists(ListNode* l1, ListNode *l2)
	{
		if (l1 == nullptr) return l2;
		if (l2 == nullptr) return l1;
		ListNode head(-1);
		ListNode *p = &head;
		while (l1 != nullptr && l2 != nullptr)
		{
			if (l1->val < l2->val)
			{
				p->next = l1;
				l1 = l1->next;
			}
			else
			{
				p->next = l2;
				l2 = l2->next;
			}
			p = p->next;
		}
		p->next = l1 == nullptr ? l2 : l1;
		return head.next;
	}
	/*Merge k Sorted Lists 两两合并超时,用优先队列*/
	struct k_sort_compare {
		bool operator()(const ListNode* l, const ListNode* r) {
			return l->val > r->val;
		}
	};
	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		if (lists.size() == 0) return NULL;

		ListNode * head = NULL;
		ListNode * ptr = NULL;
		vector<int> null_index;
		for (int i = 0; i < lists.size(); i++)
		{
			if (lists[i] == NULL) null_index.push_back(i);
		}
		cout << null_index.size() << endl;
		for (int i = null_index.size() - 1; i < null_index.size(); i--)
		{
			lists.erase(lists.begin() + null_index[i]);
		}
		priority_queue<ListNode*, vector<ListNode*>, k_sort_compare> pq;
		for (int i = 0; i<lists.size(); i++)
		{
			pq.push(lists[i]);
		}
		while (pq.size() > 0)
		{
			ListNode * m = pq.top();
			pq.pop();
			if (m->next != NULL) pq.push(m->next);
			m->next = NULL;
			if (head == NULL)
			{
				head = m;
				ptr = head;
			}
			else
			{
				ptr->next = m;
				ptr = ptr->next;
			}

		}
		return head;
	}
	/*insertion list */
	ListNode *insertionSortList(ListNode *head)
	{
		ListNode dummy(INT_MIN);
		//dummy.next = head;
		for (ListNode *cur = head; cur != nullptr;)
		{
			auto pos = findInsertPos(&dummy, cur->val);
			ListNode *tmp = cur->next;
			cur->next = pos->next;
			pos->next = cur;
			cur = tmp;
		}
		return dummy.next;
	}
	ListNode* findInsertPos(ListNode *head, int x)
	{
		ListNode *pre = nullptr;
		for (ListNode *cur = head; cur != nullptr && cur->val <= x;
			pre = cur, cur = cur->next)
			;
		return pre;
	}
	/*Sort List
	归并排序，时间复杂度 O(nlogn)，空间复杂度 O(1)*/
	ListNode* sortList(ListNode* head)
	{
		if (head == nullptr || head->next == nullptr) return head;
		ListNode *fast = head, *slow = head;
		while (fast->next != nullptr && fast->next->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		//断开
		ListNode *temp = slow;
		slow = slow->next;
		temp->next = nullptr;
		//前后半段分别排序
		ListNode *l1 = sortList(head);
		ListNode *l2 = sortList(slow);
		return mergeTwoLists(l1, l2);
	}
	/*sort colors 时间复杂度 O(n)，空间复杂度 O(1)*/
	void sortColors(vector<int> &nums)
	{
		int count[3] = { 0 };
		for (size_t i = 0; i < nums.size(); i++)
		{
			count[nums[i]]++;
		}

		int index = 0;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < count[i]; j++)
			{
				nums[index++] = i;
			}
		}
	}
	/*Search for a range*/
	class searchRange_class
	{
	public:
		/*遍历，时间复杂度为O(n),空间复杂度O(1)*/
		vector<int> searchRange(vector<int>& nums, int target)
		{
			vector<int> result = { -1, -1 };
			int flag1 = 0, flag2 = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				if (nums[i] == target)
				{
					if (flag1 == 0)
					{
						result[0] = i;
						result[1] = i;
						flag1 = 1;
					}
					else
						result[1] = i;
				}
			}
			return result;
		}
		/*使用STL 时间复杂度 O(logn)，空间复杂度 O(1)*/
		vector<int> searchRenge_STL(vector<int> &nums, int target)
		{
			vector<int> result = { -1, -1 };
			auto low = std::lower_bound(nums.begin(), nums.end(), target) - nums.begin();
			auto up = std::upper_bound(nums.begin(), nums.end(), target) - nums.begin();
			if (nums[low] == target)
			{
				result[0] = low;
				result[1] = up - 1;
			}
			return result;
		}
		/*
		重新实现 lower_bound 和 upper_bound
		时间复杂度 O(logn)，空间复杂度 O(1)
		*/
		vector<int> searchRange_imple(int A[], int n, int target)
		{
			auto lower = my_lower_bound(A, A + n, target);
			auto uppper = my_upper_bound(lower, A + n, target);
			if (lower == A + n || *lower != target)
				return vector<int> { -1, -1 };
			else
				return vector<int> {distance(A, lower), distance(A, prev(uppper))};
		}
		template<typename ForwardIterator, typename T>
		ForwardIterator my_lower_bound(ForwardIterator first,
			ForwardIterator last, T value)
		{
			while (first != last)
			{
				auto mid = next(first, distance(first, last) / 2);
				if (value > *mid) first = ++mid;
				else last = mid;
			}
			return first;
		}
		template<typename ForwardIterator, typename T>
		ForwardIterator my_upper_bound(ForwardIterator first,
			ForwardIterator last, T value)
		{
			while (first != last)
			{
				auto mid = next(first, distance(first, last) / 2);
				if (value >= *mid) first = ++mid; // 与 lower_bound 仅此不同
				else last = mid;
			}
			return first;
		}
	};
	/*
	Search Insert Position
	使用lower_bound，beat 0.01% cpp....
	*/
	int searchInsert(vector<int>& nums, int target)
	{
		return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
	}
	/*
	12ms, binary search, beats 0.47% of cpp submissions
	*/
	int searchInsert_v2(vector<int>& nums, int target)
	{
		auto first = nums.begin();
		auto last = nums.end();
		while (first != last)
		{
			auto mid = next(first, distance(first, last) / 2);
			if (target > *mid) first = ++mid;
			else last = mid;
		}
		return first-nums.begin();
	}
	/*
	Search a 2D Matrix
	二分查找,12ms
	*/
	bool searchMatrix(vector<vector<int>>& matrix, int target)
	{
		int rows = matrix.size();
		int colums = matrix[0].size();
		int length = rows*colums;
		int first = 0, last = length - 1;
		while (first <= last)
		{
			int mid = (first + last) / 2;
			if (matrix[mid / colums][mid%colums] == target)
				return true;
			else if (matrix[mid / colums][mid%colums] < target)
				first = mid + 1;
			else
				last = mid - 1;
		}
		return false;
	}
	/*
	Search a 2D Matrix 2
	900ms,beats 10% of cpp submissions
	*/
	bool searchMatrix_matrix2(vector<vector<int>>& matrix, int target)
	{
		int n = matrix[0].size();
		for (size_t i = 0; i < matrix.size(); i++)
		{
			//剪枝
			if (matrix[i][0] > target || matrix[i][n - 1] < target)
				continue;
			//二分查找
			if (std::binary_search(matrix[i].begin(), matrix[i].end(), target))
				return true;
		}
		return false;
	}
	/*
	Search a 2D Matrix 2，复杂度为O(M+N)
	272ms,beats 95%
	*/
	bool searchMatrix__matrix2_v2(vector<vector<int>>& matrix, int target) {

		int row = 0;
		int col = matrix[0].size() - 1;

		while (row < matrix.size() && col >= 0) {
			if (matrix[row][col] == target) return true;
			if (matrix[row][col] < target) { row++; continue; }
			if (matrix[row][col] > target) { col--; continue; }
		}
		return false;
		      
	}
	/*
	增量构造法，深搜，时间复杂度 O(2^n)，空间复杂度 O(n)
	每个元素都有两种选择：加入或者不加入
	*/
	vector<vector<int>> subsets(vector<int> &nums)
	{
		sort(nums.begin(), nums.end());
		vector<int> path;
		vector<vector<int>> result;
		subsets_help(result, path, 0, nums);
		return result;

	}
	void subsets_help(vector<vector<int>> &result, vector<int> &path, int step, vector<int> nums)
	{
		if (step == nums.size())
		{
			result.push_back(path);
			return;
		}
		//不选择
		subsets_help(result, path, step + 1, nums);
		path.push_back(nums[step]);
		//选择
		subsets_help(result, path, step + 1, nums);
		path.pop_back();
	}
	/*Subsets II 用subsets的代码。
	加入result之前进行判断是否存在*/
	vector<vector<int>> subsetsWithDup(vector<int> &nums)
	{
		sort(nums.begin(), nums.end());
		vector<int> path;
		vector<vector<int>> result;
		subsetsWithDup_help(result, path, 0, nums);
		return result;

	}
	void subsetsWithDup_help(vector<vector<int>> &result, vector<int> &path, int step, vector<int> nums)
	{
		if (step == nums.size())
		{
			auto it = find(result.begin(), result.end(), path);
			if (it == result.end())
				result.push_back(path);
			return;
		}
		//不选择
		subsetsWithDup_help(result, path, step + 1, nums);
		path.push_back(nums[step]);
		//选择
		subsetsWithDup_help(result, path, step + 1, nums);
		path.pop_back();
	}
	/*Permutations
	用next_permutation , 时间复杂度 O(n!)，空间复杂度 O(1)
	*/
	vector<vector<int>> permutation(vector<int>& nums)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		do
		{
			result.push_back(nums);
		} while (std::next_permutation(nums.begin(), nums.end()));
		return result;
	}
	/*假如不能使用stl，可以自己实现next_permutation*/
	template<typename BidiIt>
	bool my_next_permutation(BidiIt first, BidiIt last)
	{
		// Get a reversed range to simplify reversed traversal.
		const auto rfirst = reverse_iterator<BidiIt>(last);
		const auto rlast = reverse_iterator<BidiIt>(first);
		// Begin from the second last element to the first element.
		auto pivot = next(rfirst);
		// Find `pivot`, which is the first element that is no less than its
		// successor. `Prev` is used since `pivort` is a `reversed_iterator`.
		while (pivot != rlast && *pivot >= *prev(pivot))
			++pivot;
		// No such elemenet found, current sequence is already the largest
		// permutation, then rearrange to the first permutation and return false.
		if (pivot == rlast)
		{
			reverse(rfirst, rlast);
			return false;
		}
		// Scan from right to left, find the first element that is greater than
		// `pivot`.
		auto change = find_if(rfirst, pivot, bind1st(less<int>(), *pivot));
		swap(*change, *pivot);
		reverse(rfirst, pivot);
		return true;
	}
	/*Permutations
	用next_permutation , 时间复杂度 O(n!)，空间复杂度 O(1)
	next_permutation对于nums有重复数据也有效，不会生成重复排序
	*/
	vector<vector<int>> permutation_2(vector<int>& nums)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		do
		{
			result.push_back(nums);
		} while (std::next_permutation(nums.begin(), nums.end()));
		return result;
	}
};
int main()
{

	vector<int> vec = { 1,2,2 };
	Solution sol;
	auto res = sol.permutation(vec);
	for each (auto var in res)
	{
		for each (auto var1 in var)
		{
			cout << " " << var1;
		}
		cout << "\n";
	}
	system("pause");
	return 0;
}