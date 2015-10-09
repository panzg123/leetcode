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

};
int main()
{

	vector<int> vec = { 10, 20, 30, 30, 20, 10, 10, 20 };
	std::sort(vec.begin(), vec.end());
	Solution sol;
	return 0;
}