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
		return first - nums.begin();
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
	/*
	Combinations
	递归，时间复杂度 O(n!)，空间复杂度 O(n)
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
	result:存储结果
	n:大小
	k：开始位置
	length:已选择的数据个数
	path:选择的记录
	target：目标选择个数
	*/
	void combine_help(vector<vector<int>> &result, int n, int k, int length, vector<int> &path, int target)
	{
		if (k <= n + 1 && length == target)
		{
			result.push_back(path);
			return;
		}
		if (k > n) return;
		//选
		path.push_back(k);
		combine_help(result, n, k + 1, length + 1, path, target);
		path.pop_back();
		//不选
		combine_help(result, n, k + 1, length, path, target);
	}
	/*
	Letter Combinations of a Phone Number
	递归， 时间复杂度 O(3^n)，空间复杂度 O(n)
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
	/*Word Ladder 广度优先搜索 时间复杂度 O(n)，空间复杂度 O(n) */
	int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
		queue<string> current, next; // 当前层，下一层
		unordered_set<string> visited; // 判重
		int level = 0; // 层次
		bool found = false;
		//判断是否到达终点
		auto state_is_target = [&](const string &s)
		{
			return s == endWord;
		};
		//获取单词s可以到达的单词集合
		auto state_extend = [&](const string &s)
		{
			vector<string> result;
			for (size_t i = 0; i < s.size(); ++i)
			{
				string new_word(s);
				//改变一个字母
				for (char c = 'a'; c <= 'z'; c++)
				{
					if (c == new_word[i]) continue;
					swap(c, new_word[i]);
					//需要保证单词未被访问过
					if ((wordList.count(new_word) > 0 || new_word == endWord) &&
						!visited.count(new_word))
					{
						result.push_back(new_word);
						visited.insert(new_word);
					}
					swap(c, new_word[i]); // 恢复该单词
				}
			}
			return result;
		};
		current.push(beginWord);
		//found标记是否找到
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
						found = true; //找到了，退出
						break;
					}
				}
			}
			swap(next, current);
		}
		if (found) return level + 1;
		else return 0;
	}
	/*Word Ladder 2 递归 时间复杂度 O(n)，空间复杂度 O(n)*/
	vector<vector<string> > findLadders(string beginWord, string endWord, unordered_set<string> &wordList)
	{
		unordered_set<string> current, next; // 当前层，下一层，用集合是为了去重
		unordered_set<string> visited; // 判重
		unordered_map<string, vector<string> > father; // 树
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
					swap(c, new_word[i]); // 恢复该单词
				}
			}
			return result;
		};
		current.insert(beginWord);
		while (!current.empty() && !found)
		{
			// 先将本层全部置为已访问，防止同层之间互相指向
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
					// visited.insert(state); // 移动到最上面了
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
	Surrounded Regions BFS，时间复杂度 O(n)，空间复杂度 O(n)
	主要思想：遍历四周的每个字符，如果是‘O’，则从当前字符开始BFS遍历，如果周围是'O'，则加入队列。
	遍历完成后，进行二次扫描，如果仍被标记为'O',则表示被包围，应改为'X'；如果被标记为'+',则表示未被包围，仍为'O';
	*/
	void solve(vector<vector<char>>& board)
	{
		if (board.empty())
			return;
		const int m = board.size();
		const int n = board[0].size();
		//从四周边界开始遍历
		for (size_t i = 0; i < n; i++)
		{
			bfs(board, 0, i);
			bfs(board, m - 1, i);
		}
		for (size_t i = 1; i < m - 1; i++)
		{
			bfs(board, i, 0);
			bfs(board, i, n - 1);
		}
		//二次扫描
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
	/*Palindrome Partitioning 时间复杂度 O(2^n)，空间复杂度 O(n)
	主要思想：一个长度为 n 的字符串，有 n − 1 个地方可以砍断，每个地方可断可不断 */
	vector<vector<string>> partition(string s)
	{
		vector<vector<string>> result;
		vector<string> path; // 一个 partition 方案
		partition_help(s, path, result, 0, 1);
		return result;
	}
	// s[0, prev-1] 之间已经处理，保证是回文串
	// prev 表示 s[prev-1] 与 s[prev] 之间的空隙位置， start 同理
	void partition_help(string &s, vector<string> &path, vector<vector<string>> &result, size_t prev, size_t start)
	{
		if (start == s.size())
		{
			if (isPalindrome(s, prev, start - 1))
			{
				path.push_back(s.substr(prev, start - prev));
				result.push_back(path);
				path.pop_back();
			}
			return;
		}
		//dfs不断开
		partition_help(s, path, result, prev, start + 1);
		//如果[prev,start-1]是回文，则可以断开
		if (isPalindrome(s, prev, start - 1))
		{
			path.push_back(s.substr(prev, start - prev));
			partition_help(s, path, result, start, start + 1);
			path.pop_back();
		}
	}
	/*Palindrome Partitioning 动态规划 时间复杂度 O(n^2)，空间复杂度 O(1) */
	vector<vector<string>> partition_dp(string s)
	{
		const int LEN = 100;
		const int n = s.size();
		bool p[LEN][LEN]; // whether s[i,j] is palindrome
		//	fill_n(&p[0][0], n * n, false);
		for (int i = n - 1; i >= 0; --i)
		for (int j = i; j < n; ++j)
			p[i][j] = s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1]);
		vector<vector<string> > sub_palins[LEN]; // sub palindromes of s[0,i]
		for (int i = n - 1; i >= 0; --i)
		{
			for (int j = i; j < n; ++j)
			if (p[i][j])
			{
				const string palindrome = s.substr(i, j - i + 1);
				if (j + 1 < n)
				{
					for (auto v : sub_palins[j + 1])
					{
						v.insert(v.begin(), palindrome);
						sub_palins[i].push_back(v);
					}
				}
				else
				{
					sub_palins[i].push_back(vector<string> { palindrome });
				}
			}
		}
		return sub_palins[0];
	}
	/*Unique Paths 动态规划 时间复杂度 O(n^2)，空间复杂度 O(n)*/
	int uniquePaths(int m, int n)
	{
		const int MAX_LEN = 100;
		int dp[MAX_LEN][MAX_LEN];
		//初始化
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				dp[i][j] = 0;
			}
		}
		for (size_t i = 0; i < n; i++)
		{
			dp[0][i] = 1;
		}
		for (size_t i = 0; i < m; i++)
		{
			dp[i][0] = 1;
		}
		//状态转移：f[i][j]=f[i-1][j]+f[i][j-1]
		for (size_t i = 1; i < m; i++)
		{
			for (size_t j = 1; j < n; j++)
			{
				dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]);
			}
		}
		return dp[m - 1][n - 1];
	}
	/*DFS 时间复杂度 O(n^4)，空间复杂度 O(n)*/
	int uniquePaths_DFS(int m, int n) {
		if (m < 1 || n < 1) return 0; // 终止条件
		if (m == 1 && n == 1) return 1; // 收敛条件
		return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
	}
	/*Unique Paths 2 动态规划 时间复杂度 O(n^2)，空间复杂度 O(n)*/
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
	{
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		const int MAX_LEN = 100;
		int dp[MAX_LEN][MAX_LEN];
		//初始化
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				dp[i][j] = (obstacleGrid[i][j] == 1 ? 0 : 1);
			}
		}

		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				//第0行，状态转移：f[i][j]=f[i][j-1]
				if (i == 0 && j>0 && obstacleGrid[i][j] == 0)
					dp[0][j] = dp[0][j - 1];
				//第0列，状态转移：f[i][j]=f[i-1][j]
				if (j == 0 && i>0 && obstacleGrid[i][j] == 0)
					dp[i][0] = dp[i - 1][0];
				//状态转移：f[i][j]=f[i-1][j]+f[i][j-1]
				if (obstacleGrid[i][j] != 1 && i > 0 && j > 0)
					dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]);
			}
		}
		return dp[m - 1][n - 1];
	}
	/*N-Queens，N皇后问题，DFS 深搜 + 剪枝
	时间复杂度 O(n!)，空间复杂度 O(n)*/
	vector<vector<string>> solveNQueens(int n)
	{
		vector<vector<string>> result;
		vector<int> path;
		sloveNQueues_help(result, path, 0, n);
		return result;
	}
	void sloveNQueues_help(vector<vector<string>> &result, vector<int> &path, int start, int n)
	{
		if (start == n)
		{
			if (solve_isValid(path))
				result.push_back(get_queue(path));
			return;
		}
		if (!solve_isValid(path))
			return;
		for (size_t i = 0; i < n; i++)
		{
			//查询是否存在该选择
			auto res = find(path.begin(), path.end(), i);
			if (res != path.end()) continue;
			path.push_back(i);
			sloveNQueues_help(result, path, start + 1, n);
			path.pop_back();
		}
	}
	/*根据选择路径获取皇后排列方法*/
	vector<string> get_queue(vector<int> path)
	{
		int n = path.size();
		vector<string> res;
		for (size_t i = 0; i < n; i++)
		{
			string temp(n, '.');
			temp[path[i]] = 'Q';
			res.push_back(temp);
		}
		return res;
	}
	/*判断当前的选择队列是否有效*/
	bool solve_isValid(vector<int> path)
	{
		if (path.size() == 0) return true;
		for (size_t i = 0; i < path.size() - 1; i++)
		{
			for (size_t j = i + 1; j < path.size(); j++)
			{
				/*竖向方向，两个斜向方向*/
				if (path[j] == path[i] || path[j] == (path[i] + (j - i)) || path[j] == (path[i] - (j - i)))
					return false;
			}
		}
		return true;
	}
	/*N-Queues 2*/
	int totalNQueens(int n)
	{
		int  result = 0;
		vector<int> path;
		sloveNQueues_help(result, path, 0, n);
		return result;
	}
	void sloveNQueues_help(int &result, vector<int> &path, int start, int n)
	{
		if (start == n)
		{
			if (solve_isValid(path))
				result++;
			return;
		}
		if (!solve_isValid(path))
			return;
		for (size_t i = 0; i < n; i++)
		{
			//查询是否存在该选择
			auto res = find(path.begin(), path.end(), i);
			if (res != path.end()) continue;
			path.push_back(i);
			sloveNQueues_help(result, path, start + 1, n);
			path.pop_back();
		}
	}
	/*Restore IP Addresses 时间复杂度 O(n^4)，空间复杂度 O(n)*/
	vector<string> restoreIpAddresses(string s)
	{
		vector<string> result;
		string ip; // 存放中间结果
		restoreIpAddresses_dfs(s, 0, 0, ip, result);
		return result;
	}
	/**
	* @brief 解析字符串
	* @param[in] s 字符串，输入数据
	* @param[in] startIndex 从 s 的哪里开始
	* @param[in] step 当前步骤编号，从 0 开始编号，取值为 0,1,2,3,4 表示结束了
	* @param[out] intermediate 当前解析出来的中间结果
	* @param[out] result 存放所有可能的 IP 地址
	* @return 无
	*/
	void restoreIpAddresses_dfs(string s, size_t start, size_t step, string ip,
		vector<string> &result)
	{
		if (start == s.size() && step == 4)   // 找到一个合法解
		{
			ip.resize(ip.size() - 1);
			result.push_back(ip);
			return;
		}
		if (s.size() - start > (4 - step) * 3)
			return; // 剪枝
		if (s.size() - start < (4 - step))
			return; // 剪枝
		int num = 0;
		for (size_t i = start; i < start + 3; i++)
		{
			num = num * 10 + (s[i] - '0');
			if (num <= 255)   // 当前结点合法，则继续往下递归
			{
				ip += s[i];
				restoreIpAddresses_dfs(s, i + 1, step + 1, ip + '.', result);
			}
			if (num == 0) break; // 不允许前缀 0，但允许单个 0
		}
	}

private:
	/*Surrounded Regions BFS*/
	void bfs(vector<vector<char>> &board, int i, int j)
	{
		typedef pair<int, int> state_t;
		queue<state_t> q;
		const int m = board.size();
		const int n = board[0].size();
		/*判断当前字符是否是'O'*/
		auto is_valid = [&](const state_t &s)
		{
			const int x = s.first;
			const int y = s.second;
			if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != 'O')
				return false;
			return true;
		};
		//匿名函数，返回当前字符s的四周'O'集合
		auto state_extend = [&](const state_t &s)
		{
			vector<state_t> result;
			const int x = s.first;
			const int y = s.second;
			//上下左右
			const state_t new_states[4] = { { x - 1, y }, { x + 1, y }, { x, y - 1 }, { x, y + 1 } };
			for (size_t i = 0; i < 4; i++)
			{
				if (is_valid(new_states[i]))
				{
					//既有标记又有去重的功能
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
	/*判断是否是回文，start和end表示起始和结束位置*/
	bool isPalindrome(const string &s, int start, int end)
	{
		while (start < end && s[start] == s[end])
		{
			++start;
			--end;
		}
		return start >= end;
	}
	vector<string> keyboard;// = { " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
};
int main()
{


	Solution sol;
	auto res = sol.totalNQueens(4);
	cout << res;
	system("pause");
	return 0;
}