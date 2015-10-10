#include"header.h"
using namespace std;
class Solution
{
public:
	/*merge sorted array
	ʱ�临�Ӷ� O(m+n)���ռ临�Ӷ� O(1)*/
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
	/*Merge Two Sorted Lists ʱ�临�Ӷ� O(min(m,n))���ռ临�Ӷ� O(1)*/
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
	/*Merge k Sorted Lists �����ϲ���ʱ,�����ȶ���*/
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
	�鲢����ʱ�临�Ӷ� O(nlogn)���ռ临�Ӷ� O(1)*/
	ListNode* sortList(ListNode* head)
	{
		if (head == nullptr || head->next == nullptr) return head;
		ListNode *fast = head, *slow = head;
		while (fast->next != nullptr && fast->next->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		//�Ͽ�
		ListNode *temp = slow;
		slow = slow->next;
		temp->next = nullptr;
		//ǰ���ηֱ�����
		ListNode *l1 = sortList(head);
		ListNode *l2 = sortList(slow);
		return mergeTwoLists(l1, l2);
	}
	/*sort colors ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(1)*/
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
		/*������ʱ�临�Ӷ�ΪO(n),�ռ临�Ӷ�O(1)*/
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
		/*ʹ��STL ʱ�临�Ӷ� O(logn)���ռ临�Ӷ� O(1)*/
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
		����ʵ�� lower_bound �� upper_bound
		ʱ�临�Ӷ� O(logn)���ռ临�Ӷ� O(1)
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
				if (value >= *mid) first = ++mid; // �� lower_bound ���˲�ͬ
				else last = mid;
			}
			return first;
		}
	};
	/*
	Search Insert Position
	ʹ��lower_bound��beat 0.01% cpp....
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
		return first - nums.begin();
	}
	/*
	Search a 2D Matrix
	���ֲ���,12ms
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
			//��֦
			if (matrix[i][0] > target || matrix[i][n - 1] < target)
				continue;
			//���ֲ���
			if (std::binary_search(matrix[i].begin(), matrix[i].end(), target))
				return true;
		}
		return false;
	}
	/*
	Search a 2D Matrix 2�����Ӷ�ΪO(M+N)
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
	�������취�����ѣ�ʱ�临�Ӷ� O(2^n)���ռ临�Ӷ� O(n)
	ÿ��Ԫ�ض�������ѡ�񣺼�����߲�����
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
		//��ѡ��
		subsets_help(result, path, step + 1, nums);
		path.push_back(nums[step]);
		//ѡ��
		subsets_help(result, path, step + 1, nums);
		path.pop_back();
	}
	/*Subsets II ��subsets�Ĵ��롣
	����result֮ǰ�����ж��Ƿ����*/
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
		//��ѡ��
		subsetsWithDup_help(result, path, step + 1, nums);
		path.push_back(nums[step]);
		//ѡ��
		subsetsWithDup_help(result, path, step + 1, nums);
		path.pop_back();
	}
	/*Permutations
	��next_permutation , ʱ�临�Ӷ� O(n!)���ռ临�Ӷ� O(1)
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
	/*���粻��ʹ��stl�������Լ�ʵ��next_permutation*/
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
	��next_permutation , ʱ�临�Ӷ� O(n!)���ռ临�Ӷ� O(1)
	next_permutation����nums���ظ�����Ҳ��Ч�����������ظ�����
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
	/*
	Combinations
	�ݹ飬ʱ�临�Ӷ� O(n!)���ռ临�Ӷ� O(n)
	*/
	vector<vector<int>> combine(int n, int k)
	{
		vector<vector<int>> result;
		if (n < k) return result;
		vector<int> path;
		combine_help(result, n, 1, 0, path, k);
		return result;
	}
	/*
	result:�洢���
	n:��С
	k����ʼλ��
	length:��ѡ������ݸ���
	path:ѡ��ļ�¼
	target��Ŀ��ѡ�����
	*/
	void combine_help(vector<vector<int>> &result, int n, int k, int length, vector<int> &path, int target)
	{
		if (k <= n + 1 && length == target)
		{
			result.push_back(path);
			return;
		}
		if (k > n) return;
		//ѡ
		path.push_back(k);
		combine_help(result, n, k + 1, length + 1, path, target);
		path.pop_back();
		//��ѡ
		combine_help(result, n, k + 1, length, path, target);
	}
	/*
	Letter Combinations of a Phone Number
	�ݹ飬 ʱ�临�Ӷ� O(3^n)���ռ临�Ӷ� O(n)
	*/
	vector<string> letterCombinations(string digits)
	{
		vector<string> result;
		if (digits == "") return result;
		letterCombinations_help(digits, 0, "", result);
		return result;
	}
	void letterCombinations_help(const string& digits, size_t cur, string path, vector<string> &result)
	{
		if (cur == digits.size())
		{
			result.push_back(path);
			return;
		}
		for (auto s : keyboard[digits[cur] - '0'])
		{
			letterCombinations_help(digits, cur + 1, path + s, result);
		}
		return;
	}
	/*Word Ladder ����������� ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(n) */
	int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
		queue<string> current, next; // ��ǰ�㣬��һ��
		unordered_set<string> visited; // ����
		int level = 0; // ���
		bool found = false;
		//�ж��Ƿ񵽴��յ�
		auto state_is_target = [&](const string &s)
		{
			return s == endWord;
		};
		//��ȡ����s���Ե���ĵ��ʼ���
		auto state_extend = [&](const string &s)
		{
			vector<string> result;
			for (size_t i = 0; i < s.size(); ++i)
			{
				string new_word(s);
				//�ı�һ����ĸ
				for (char c = 'a'; c <= 'z'; c++)
				{
					if (c == new_word[i]) continue;
					swap(c, new_word[i]);
					//��Ҫ��֤����δ�����ʹ�
					if ((wordList.count(new_word) > 0 || new_word == endWord) &&
						!visited.count(new_word))
					{
						result.push_back(new_word);
						visited.insert(new_word);
					}
					swap(c, new_word[i]); // �ָ��õ���
				}
			}
			return result;
		};
		current.push(beginWord);
		//found����Ƿ��ҵ�
		while (!current.empty() && !found)
		{
			++level;
			while (!current.empty() && !found)
			{
				const string str = current.front();
				current.pop();
				const auto& new_states = state_extend(str);
				for (const auto& state : new_states)
				{
					next.push(state);
					if (state_is_target(state))
					{
						found = true; //�ҵ��ˣ��˳�
						break;
					}
				}
			}
			swap(next, current);
		}
		if (found) return level + 1;
		else return 0;
	}
	/*Word Ladder 2 �ݹ� ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(n)*/
	vector<vector<string> > findLadders(string beginWord, string endWord,unordered_set<string> &wordList)
	{
		unordered_set<string> current, next; // ��ǰ�㣬��һ�㣬�ü�����Ϊ��ȥ��
		unordered_set<string> visited; // ����
		unordered_map<string, vector<string> > father; // ��
		bool found = false;
		auto state_is_target = [&](const string &s)
		{
			return s == endWord;
		};
		auto state_extend = [&](const string &s)
		{
			unordered_set<string> result;
			for (size_t i = 0; i < s.size(); ++i)
			{
				string new_word(s);
				for (char c = 'a'; c <= 'z'; c++)
				{
					if (c == new_word[i]) continue;
					swap(c, new_word[i]);
					if ((wordList.count(new_word) > 0 || new_word == endWord) &&
						!visited.count(new_word))
					{
						result.insert(new_word);
					}
					swap(c, new_word[i]); // �ָ��õ���
				}
			}
			return result;
		};
		current.insert(beginWord);
		while (!current.empty() && !found)
		{
			// �Ƚ�����ȫ����Ϊ�ѷ��ʣ���ֹͬ��֮�以��ָ��
			for (const auto& word : current)
				visited.insert(word);
			for (const auto& word : current)
			{
				const auto new_states = state_extend(word);
				for (const auto &state : new_states)
				{
					if (state_is_target(state)) found = true;
					next.insert(state);
					father[state].push_back(word);
					// visited.insert(state); // �ƶ�����������
				}
			}
			current.clear();
			swap(current, next);
		}
		vector<vector<string> > result;
		if (found)
		{
			vector<string> path;
			gen_path(father, path, beginWord, endWord, result);
		}
		return result;
	}
	void gen_path(unordered_map<string, vector<string> > &father,
		vector<string> &path, const string &start, const string &word,
		vector<vector<string> > &result)
	{
		path.push_back(word);
		if (word == start)
		{
			result.push_back(path);
			reverse(result.back().begin(), result.back().end());
		}
		else
		{
			for (const auto& f : father[word])
			{
				gen_path(father, path, start, f, result);
			}
		}
		path.pop_back();
	}
	/*
	Surrounded Regions BFS��ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(n)
	��Ҫ˼�룺�������ܵ�ÿ���ַ�������ǡ�O������ӵ�ǰ�ַ���ʼBFS�����������Χ��'O'���������С�
	������ɺ󣬽��ж���ɨ�裬����Ա����Ϊ'O',���ʾ����Χ��Ӧ��Ϊ'X'����������Ϊ'+',���ʾδ����Χ����Ϊ'O';
	*/
	void solve(vector<vector<char>>& board)
	{
		if (board.empty())
			return;
		const int m = board.size();
		const int n = board[0].size();
		//�����ܱ߽翪ʼ����
		for (size_t i = 0; i < n; i++)
		{
			bfs(board, 0, i);
			bfs(board, m - 1, i);
		}
		for (size_t i = 1; i < m-1; i++)
		{
			bfs(board, i, 0);
			bfs(board, i, n - 1);
		}
		//����ɨ��
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				if (board[i][j] == 'O')
					board[i][j] = 'X';
				else if (board[i][j] == '+')
					board[i][j] = 'O';
			}
		}
	}
private:
	void bfs(vector<vector<char>> &board, int i, int j)
	{
		typedef pair<int, int> state_t;
		queue<state_t> q;
		const int m = board.size();
		const int n = board[0].size();
		/*�жϵ�ǰ�ַ��Ƿ���'O'*/
		auto is_valid = [&](const state_t &s)
		{
			const int x = s.first;
			const int y = s.second;
			if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != 'O')
				return false;
			return true;
		};
		//�������������ص�ǰ�ַ�s������'O'����
		auto state_extend = [&](const state_t &s)
		{
			vector<state_t> result;
			const int x = s.first;
			const int y = s.second;
			//��������
			const state_t new_states[4] = { { x - 1, y }, { x + 1, y }, { x, y - 1 }, { x, y + 1 } };
			for (size_t i = 0; i < 4; i++)
			{
				if (is_valid(new_states[i]))
				{
					//���б������ȥ�صĹ���
					board[new_states[i].first][new_states[i].second] = '+';
					result.push_back(new_states[i]);
				}
			}
			return result;
		};
		//BFS
		state_t start = { i, j };
		if (is_valid(start))
		{
			board[i][j] = '+';
			q.push(start);
		}
		while (!q.empty())
		{
			auto cur = q.front();
			q.pop();
			auto new_states = state_extend(cur);
			for (auto s : new_states)
				q.push(s);
		}
	}
	vector<string> keyboard;// = { " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
};
int main()
{

	vector<vector<char>> board;
	vector<char> c1 = { 'X', 'X', 'X' };
	vector<char> c2 = { 'X', 'O', 'X' };
	vector<char> c3 = { 'X', 'X', 'X' };
	board.push_back(c1);
	board.push_back(c2);
	board.push_back(c3);

	Solution sol;
	sol.solve(board);
	for each (auto var in board)
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