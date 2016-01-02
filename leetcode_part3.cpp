#include"header.h"
using namespace std;
namespace panzg_leetcode
{
	class Solution
	{
	public:
		/*Spiral Matrix*/
		vector<int> spiralOrder(vector<vector<int>>& matrix)
		{
			vector<int> result;
			if (matrix.empty())
				return result;
			int beginX = 0, endX = matrix[0].size() - 1;
			int beginY = 0, endY = matrix.size() - 1;
			while (true)
			{
				//上
				for (int j = beginX; j <= endX; ++j)
					result.push_back(matrix[beginY][j]);
				if (++beginY > endY)
					break;
				//右
				for (int i = beginY; i <= endY; ++i)
					result.push_back(matrix[i][endX]);
				if (beginX > --endX)
					break;
				//下
				for (int j = endX; j >= beginX; --j)
					result.push_back(matrix[endY][j]);
				if (--endY < beginY)
					break;
				//左
				for (int i = endY; i >= beginY; --i)
					result.push_back(matrix[i][beginX]);
				if (++beginX > endX)
					break;
			}
			return result;
		}
		/*Spiral Matrix 2*/
		vector<vector<int>> generateMatrix(int n)
		{
			vector<vector<int>> matrix(n, vector<int>(n));
			int begin = 0, end = n - 1;
			int num = 1;
			while (begin < end)
			{
				for (int i = begin; i < end; ++i)
					matrix[begin][i] = num++;
				for (int i = begin; i < end; ++i)
					matrix[i][end] = num++;
				for (int j = end; j > begin; --j)
					matrix[end][j] = num++;
				for (int i = end; i > begin; --i)
					matrix[i][begin] = num++;
				++begin;
				--end;
			}
			if (begin == end) matrix[begin][begin] = num;
			return matrix;
		}
		/*ZigZag Conversion 数学规律*/
		string convert(string s, int numRows)
		{
			if (numRows <= 1 || s.size() <= 1)
				return s;
			string result;
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0, index = i; index < s.size(); j++, index = (2 * numRows - 2) * j + i)
				{
					result.append(1, s[index]); // 垂直元素
					if (i == 0 || i == numRows - 1)
						continue; // 斜对角元素
					if (index + (numRows - i - 1) * 2 < s.size())
						result.append(1, s[index + (numRows - i - 1) * 2]);
				}
			}
			return result;
		}
		/*Divide Two Integers*/
		//int divide(int dividend, int divisor)
		//{
		//	if (!divisor) return INT_MAX;
		//	if (divisor == 1) return dividend;
		//	if (divisor == -1){
		//		if (dividend == INT_MIN) { return INT_MAX; }
		//		else { return -dividend; }
		//	}

		//	bool s1 = dividend < 0;
		//	bool s2 = divisor < 0;

		//	unsigned int nom = s1 ? -dividend : dividend;
		//	unsigned int den = s2 ? -divisor : divisor;

		//	unsigned int rem = 0;
		//	unsigned int quot = 0;

		//	for (int i = 31; i >= 0; --i){
		//		rem <<= 1;
		//		rem |= (nom >> i) & 1;
		//		if (rem >= den){
		//			rem -= den;
		//			quot |= (1 << i);
		//		}
		//	}

		//	return s1^s2 ? -quot : quot;
		//}
		// LeetCode, Text Justification
		// 时间复杂度 O(n)，空间复杂度 O(1)
		vector<string> fullJustify(vector<string> &words, int L)
		{
			vector<string> result;
			const int n = words.size();
			int begin = 0, len = 0; // 当前行的起点，当前长度
			for (int i = 0; i < n; ++i) {
				if (len + words[i].size() + (i - begin) > L)
				{
					result.push_back(connect(words, begin, i - 1, len, L, false));
					begin = i;
					len = 0;
				}
				len += words[i].size();
			}
			// 最后一行不足 L
			result.push_back(connect(words, begin, n - 1, len, L, true));
			return result;
		}
		/**
		* @brief 将 words[begin, end] 连成一行
		* @param[in] words 单词列表
		* @param[in] begin 开始
		* @param[in] end 结束
		* @param[in] len words[begin, end] 所有单词加起来的长度
		* @param[in] L 题目规定的一行长度
		* @param[in] is_last 是否是最后一行
		* @return 对齐后的当前行
		*/
		string connect(vector<string> &words, int begin, int end, int len, int L, bool is_last)
		{
			string s;
			int n = end - begin + 1;
			for (int i = 0; i < n; ++i)
			{
				s += words[begin + i];
				addSpaces(s, i, n - 1, L - len, is_last);
			}
			if (s.size() < L) s.append(L - s.size(), ' ');
			return s;
		}
		/**
		* @brief 添加空格.
		* @param[inout]s 一行
		* @param[in] i 当前空隙的序号
		* @param[in] n 空隙总数
		* @param[in] L 总共需要添加的空额数
		* @param[in] is_last 是否是最后一行
		* @return 无
		*/
		void addSpaces(string &s, int i, int n, int L, bool is_last)
		{
			if (n < 1 || i > n - 1) return;
			int spaces = is_last ? 1 : (L / n + (i < (L % n) ? 1 : 0));
			s.append(spaces, ' ');
		}
		//LeetCode, Max Points on a Line
		// 暴力枚举法，以边为中心，时间复杂度 O(n^3)，空间复杂度 O(1)
		int maxPoints(vector<Point>& points)
		{
			if (points.size() < 3)
				return points.size();
			int result = 0;

			for (int i = 0; i < points.size() - 1; i++)
			{
				for (int j = i + 1; j < points.size(); j++)
				{
					int sign = 0;
					int a, b, c;
					if (points[i].x == points[j].x)
						sign = 1;
					else
					{
						a = points[j].x - points[i].x;
						b = points[j].y - points[i].y;
						c = a*points[i].y - b*points[i].x;
					}
					int count = 0;
					for (int k = 0; k < points.size(); k++)
					{
						if ((0 == sign && a*points[k].y == c + b*points[k].x) ||
							(1 == sign && points[k].x == points[j].x))
							count++;
					}
					if (count > result)
						result = count;
				}
			}
			return result;
		}

		/*
		该方法的核心是将原问题转变成一个寻找第k小数的问题（假设两个原序列升序排列），这样中位数实际上是第(m+n)/2小的数。所以只要解决了第k小数的问题，原问题也得以解决。

		首先假设数组A和B的元素个数都大于k/2，我们比较A[k/2-1]和B[k/2-1]两个元素，这两个元素分别表示A的第k/2小的元素和B的第k/2小的元素。这两个元素比较共有三种情况：>、<和=。如果A[k/2-1]<B[k/2-1]，这表示A[0]到A[k/2-1]的元素都在A和B合并之后的前k小的元素中。换句话说，A[k/2-1]不可能大于两数组合并之后的第k小值，所以我们可以将其抛弃。

		证明也很简单，可以采用反证法。假设A[k/2-1]大于合并之后的第k小值，我们不妨假定其为第（k+1）小值。由于A[k/2-1]小于B[k/2-1]，所以B[k/2-1]至少是第（k+2）小值。但实际上，在A中至多存在k/2-1个元素小于A[k/2-1]，B中也至多存在k/2-1个元素小于A[k/2-1]，所以小于A[k/2-1]的元素个数至多有k/2+ k/2-2，小于k，这与A[k/2-1]是第（k+1）的数矛盾。

		当A[k/2-1]>B[k/2-1]时存在类似的结论。

		当A[k/2-1]=B[k/2-1]时，我们已经找到了第k小的数，也即这个相等的元素，我们将其记为m。由于在A和B中分别有k/2-1个元素小于m，所以m即是第k小的数。(这里可能有人会有疑问，如果k为奇数，则m不是中位数。这里是进行了理想化考虑，在实际代码中略有不同，是先求k/2，然后利用k-k/2获得另一个数。)

		通过上面的分析，我们即可以采用递归的方式实现寻找第k小的数。此外我们还需要考虑几个边界条件：

		如果A或者B为空，则直接返回B[k-1]或者A[k-1]；
		如果k为1，我们只需要返回A[0]和B[0]中的较小值；
		如果A[k/2-1]=B[k/2-1]，返回其中一个；
		*/
		double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
		{
			int k = nums1.size() + nums2.size();
			//偶数
			if (k % 2 == 0)
				return (
				findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2) +
				findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2 + 1)
				) / 2;
			//奇数
			else
				return findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2 + 1);
		}
		double findKthSortedArrays(vector<int>::const_iterator nums1, int m, vector<int>::const_iterator nums2, int n, int k)
		{
			if (m > n)
				return findKthSortedArrays(nums2, n, nums1, m, k);
			//边界条件
			if (m == 0)
				return *(nums2 + k - 1);
			//返回第1小的值，即min(num[0],num1[0])
			if (k == 1)
				return min(*nums1, *nums2);

			//下面是判断B[k-1]和A[k-1]关系；
			int mk = min(m, k / 2);
			int nk = k - mk;
			//如果A[k/2-1]=B[k/2-1]，返回其中一个；
			if (*(nums1 + mk - 1) == *(nums2 + nk - 1))
				return *(nums1 + mk - 1);
			//当A[k/2-1] < B[k/2-1],删除A[0，k/2-1]
			else if (*(nums1 + mk - 1) < *(nums2 + nk - 1))
				return findKthSortedArrays(nums1 + mk, m - mk, nums2, n, k - mk);
			//当A[k/2-1] > B[k/2-1],删除B[0，k/2-1]
			else
				return findKthSortedArrays(nums1, m, nums2 + nk, n - nk, k - nk);
		}
		/*Swap Nodes in Pairs*/
		ListNode* swapPairs(ListNode* head)
		{
			if (head == nullptr || head->next == nullptr)
				return head;
			ListNode my_head(-1);
			my_head.next = head;
			ListNode * pre = head, *cur = head->next, *last = &my_head;
			while (1)
			{
				last->next = cur;
				pre->next = cur->next;
				cur->next = pre;
				if (!(pre->next && pre->next->next))
					break;
				else
				{
					last = pre;
					pre = pre->next;
					cur = pre->next;
				}
			}
			return my_head.next;
		}
		/*Reverse Nodes in k-Group 使用栈进行保存*/
		ListNode* reverseKGroup(ListNode* head, int k)
		{
			stack<ListNode*> stack_node;
			int flag = 0; //判断是否是整个链表的第一个节点
			ListNode * last_node = nullptr;  //记录最后一个节点
			ListNode * my_head = nullptr; //记录首节点，进行返回
			ListNode * temp = nullptr; //临时节点
			int count = 0; //计数器，入栈一个count++
			while (head)
			{
				//压入k个节点
				while (head && count < k)
				{
					stack_node.push(head);
					head = head->next;
					count++;
				}
				//如果个数足够
				if (count == k)
				{
					for (int i = 0; i < k; i++)
					{
						temp = stack_node.top();
						if (!flag) //第一个节点，需要赋值给my_head
						{
							flag = 1;
							my_head = temp;
						}
						if (last_node != nullptr)  //链到尾部
						{
							last_node->next = temp;
						}
						last_node = temp;
						stack_node.pop();
					}
					last_node->next = nullptr;
					count = 0;
				}
				//尾部个数不够
				else
				{
					for (int i = 0; i < count; i++)
					{
						temp = stack_node.top();
						stack_node.pop();
					}
					if (!flag) //第一个节点，需要赋值给my_head
					{
						flag = 1;
						my_head = temp;
					}
					if (last_node != nullptr)  //链到尾部
					{
						last_node->next = temp;
					}
				}
			}
			return my_head;
		}
		/*First Missing Positive 时间复杂度和空间复杂度都是o(n)，不符合要求*/
		int firstMissingPositive(vector<int>& nums)
		{
			unordered_map<int, bool> m_map;
			for (int i = 0; i < nums.size(); i++)
			{
				m_map[nums[i]] = true;
			}
			int index = 1;
			for (int i = 0; i < nums.size(); i++)
			{
				auto res = m_map.find(index);
				if (res == m_map.end())
				{
					return index;
				}
				else
					index++;
			}
			return index;
		}
		/*first missing positive 空间复杂度为常数
		思路：可以把数组中的元素放入“合适”的位置时，例如将1放在0位置上，2放在1位置上。。。，最后遍历数组，如果某个位置上的数不合适，则返回该位置上“合适”的数，
		*/
		int firstMissingPositive_v2(vector<int> &nums)
		{
			int size = nums.size();
			if (size == 0) return 1;
			for (int i = 1; i <= size; i++)
			{
				//将元素放入合适的位置
				while (nums[i - 1] != i)
				{
					if (nums[i - 1]<0 || nums[i - 1]>size || nums[i - 1] == nums[nums[i - 1] - 1])
					{
						break;
					}
					int temp = nums[i - 1];
					nums[i - 1] = nums[temp - 1];
					nums[temp - 1] = temp;
				}
			}
			for (int i = 1; i <= size; i++)
			{
				if (nums[i - 1] != i)
					return i;
			}
			return size + 1;
		}
		/*Plus One 将数组代表的整数加1*/
		vector<int> plusOne(vector<int>& digits)
		{
			int flag = 0;
			for (auto iter = digits.rbegin(); iter != digits.rend(); iter++)
			{
				int temp = (*iter + flag);
				if (iter == digits.rbegin())
				{
					temp += 1;
				}
				flag = temp / 10;
				*iter = temp % 10;
			}
			if (flag > 0)
				digits.insert(digits.begin(), flag);
			return digits;
		}
		/*Search in Rotated Sorted Array II*/
		bool search(vector<int>& nums, int target)
		{
			auto res = find(nums.begin(), nums.end(), target);
			if (res == nums.end())
				return false;
			else
				return true;
		}
		/*Symmetric Tree 递归*/
		bool isSymmetric(TreeNode* root)
		{
			if (root == nullptr)
				return true;
			else
				return isSymmetric_helper(root->left, root->right);
		}
		bool isSymmetric_helper(TreeNode* left, TreeNode* right)
		{
			if (left == nullptr && right == nullptr)
				return true;
			if (left == nullptr || right == nullptr)
				return false;
			return left->val == right->val && isSymmetric_helper(left->left, right->right)
				&& isSymmetric_helper(left->right, right->left);
		}
		/*Maximum Depth of Binary Tree 递归*/
		int maxDepth(TreeNode* root)
		{
			return maxDepth_helper(root, 0);
		}
		int maxDepth_helper(TreeNode* root, int depth)
		{
			if (root == nullptr)
				return depth;
			else
				return max(maxDepth_helper(root->left, depth + 1), maxDepth_helper(root->right, depth + 1));
		}
		/*Longest Consecutive Sequence 偷懒不符合O(n)要求*/
		int longestConsecutive_v1(vector<int>& nums)
		{
			sort(nums.begin(), nums.end());
			int count = 1;
			int result = 1;
			for (size_t i = 1; i < nums.size(); i++)
			{
				if (nums[i] == nums[i - 1] + 1)
					count++;
				else if (nums[i] == nums[i - 1])
				{
					continue;
				}
				else
				{
					result = max(result, count);
					count = 1;
				}
			}
			return max(result, count);
		}
		/*Longest Consecutive Sequence,用unordered_set，O(n)*/
		int longestConsecutive(vector<int>& nums)
		{
			int len = 0, candidate, val;
			unordered_set<int> set(nums.begin(), nums.end());
			while (!set.empty())
			{
				val = *set.begin();
				set.erase(val);
				candidate = 1;
				//处理比val大的数
				for (int i = val + 1; set.find(i) != set.end(); ++i)
				{
					set.erase(i);
					candidate++;
				}
				//处理比val小的数
				for (int i = val - 1; set.find(i) != set.end(); --i)
				{
					set.erase(i);
					candidate++;
				}
				len = max(len, candidate);
			}
			return len;
		}
		/*Copy List with Random Pointer 使用unordered_map,时间复杂度、空间复杂度都为O(N)*/
		RandomListNode *copyRandomList(RandomListNode *head)
		{
			unordered_map<RandomListNode*, RandomListNode*> result;
			RandomListNode* m_head = head;
			while (m_head != nullptr)
			{
				RandomListNode * node = new RandomListNode(m_head->label);
				result[m_head] = node;
				m_head = m_head->next;
			}
			m_head = head;
			while (m_head)
			{
				if (m_head->next != nullptr)
					result[m_head]->next = result[m_head->next];
				if (m_head->random != nullptr)
					result[m_head]->random = result[m_head->random];
				m_head = m_head->next;
			}
			return result[head];
		}
		/*Reverse Words in a String 用栈*/
		void reverseWords(string &s)
		{
			stack<string> st;
			st = reverseWords_helper(s, " ");
			s.clear();
			while (!st.empty())
			{
				string str = st.top();
				if (str != "")
					s += (str + " ");
				st.pop();
			}
			if (s.size() > 1)
				s.erase(s.size() - 1);
		}
		/*Reverse Words in a String 局部翻转，然后整体翻转*/
		void reverseWords_v2(string &s)
		{
			reverseWords_v2_remove_space(s);
			if (s[0] == ' ')
				s.erase(0, 1);
			if (s == "") return;
			int prev = 0;
			if (s[s.size() - 1] != ' ')
				s += " ";
			for (int i = 1; i < s.size(); i++)
			{
				if (s[i] != ' '&& s[i - 1] == ' ')
					prev = i;
				else if (s[i] == ' ')
					reverseWords_v2_helper(s, prev, i - 1);
			}
			if (s[s.size() - 1] == ' ')
				s.erase(s.size() - 1);
			reverseWords_v2_helper(s, 0, s.size() - 1);
		}
		void reverseWords_v2_helper(string& s, int start, int end)
		{
			while (start < end)
			{
				char temp = s[start];
				s[start] = s[end];
				s[end] = temp;
				start++;
				end--;
			}
		}
		void reverseWords_v2_remove_space(string& s)
		{
			int i = 1;
			while (i < s.size())
			{
				if (s[i - 1] == ' '&&s[i] == ' ')
					s.erase(i, 1);
				else
					i++;
			}
		}
		/*字符串分割函数，结果存储在stack中*/
		stack<std::string> reverseWords_helper(std::string str, std::string pattern)
		{
			std::string::size_type pos;
			std::stack<std::string> result;
			str += pattern;//扩展字符串以方便操作
			int size = str.size();
			for (int i = 0; i < size; i++)
			{
				pos = str.find(pattern, i);
				if (pos < size)
				{
					std::string s = str.substr(i, pos - i);
					result.push(s);
					i = pos + pattern.size() - 1;
				}
			}
			return result;
		}
		/*Linked List Cycle,判断链表是否有环,经典快慢指针问题*/
		bool hasCycle(ListNode *head)
		{
			ListNode* fast = head;
			ListNode* slow = head;
			while (fast)
			{
				if (fast->next)
					fast = fast->next->next;
				else
					return false;
				slow = slow->next;
				if (fast == slow)
					return true;
			}
			return false;
		}
		/*Linked List Cycle 2，找环的起点，经典快慢指针问题*/
		ListNode *detectCycle(ListNode *head)
		{
			if (!head) return 0;

			ListNode *fast = head, *slow = head;
			if (fast->next && fast->next->next)
			{
				do
				{
					fast = fast->next->next;
					slow = slow->next;
				} while (fast != slow && fast->next && fast->next->next);

				// the point is when two pointers meet, the distance from the position 
				// to the entry is equal to the distance from head to the entry

				if (fast == slow)
				{
					for (fast = head; fast != slow; fast = fast->next, slow = slow->next);
					return fast;
				}
			}
			return 0;
		}
		/*Reorder List 用栈或者数组记录位置，空间复杂度有点高*/
		void reorderList(ListNode* head)
		{
			ListNode *my_head = head;
			vector<ListNode*> node_vec; //记录指针
			while (my_head)
			{
				node_vec.push_back(my_head);
				my_head = my_head->next;
			}
			int length = node_vec.size();
			int i = 0, j = length - 1;
			ListNode *m_head = new ListNode(-1);
			m_head->next = head;
			ListNode *cur = m_head;
			while (i < j)  //交替链接
			{
				cur->next = node_vec[i];
				cur = cur->next;
				i++;
				cur->next = node_vec[j];
				cur = cur->next;
				j--;
			}
			if (i == j)
			{
				cur->next = node_vec[i];
				cur->next->next = nullptr;
			}
			else
				cur->next = nullptr;
		}
		class Entry
		{
		public:
			int key;
			int value;
			Entry(int key, int value) :key(key), value(value){};
		};
		class LRUCache
		{
		public:
			int capacity, currentSize;
			unordered_map < int, list<Entry*>::iterator> hash;
			list<Entry*> lru; // front is the lastest
		public:
			LRUCache(int capacity) :capacity(capacity), currentSize(0)
			{

			}
			int get(int key)
			{
				Entry *entry = nullptr;
				auto it = hash.find(key);
				if (it == hash.end())
					return -1;
				else
				{
					//让it指向的元素移动到lru链表的首部
					lru.splice(lru.begin(), lru, it->second);
					return (*(it->second))->value;
				}
			}
			void set(int key, int value)
			{
				Entry *entry = nullptr;
				auto it = hash.find(key);
				if (it == hash.end()) //不存在key
				{
					entry = new Entry(key, value);
					if (currentSize >= capacity) //空间用尽，删除首部元素
					{
						hash.erase(lru.back()->key);
						delete lru.back();
						lru.pop_back();
					}
					else
						currentSize++;
					lru.push_front(entry);
					hash[key] = lru.begin();
				}
				else
				{
					(*(it->second))->value = value;
					lru.splice(lru.begin(), lru, it->second); //移动到首部
				}
			}
		};
		/*Maximum Product Subarray 直接两层循环，超时*/
		int maxProduct(vector<int>& nums)
		{
			int length = nums.size();
			int result = INT_MIN;
			for (int i = 0; i < length; i++)
			{
				int temp = 1;
				for (int j = i; j < length; j++)
				{
					temp *= nums[j];
					result = max(result, temp);
				}
			}
			return result;
		}
		/*
		动态规划，当前状态包含三种情况：
		1. current maxValue * A[i]  if A[i]>0
		2. current minValue * A[i]  if A[i]<0
		3. A[i]
		所以代码中需要记录当前最小值和当前最大值两个值
		*/
		int maxProduct_dp(vector<int>& nums)
		{
			int length = nums.size();
			if (length <= 0) return 0;
			if (length == 1) return nums[0];
			int curMax = nums[0];
			int curMin = nums[0];
			int result = nums[0];
			for (int i = 1; i < length; i++)
			{
				int temp_max = nums[i] * curMax;
				int temp_min = nums[i] * curMin;
				curMax = max(max(temp_max, temp_min), nums[i]);
				curMin = min(min(temp_max, temp_min), nums[i]);
				result = max(result, curMax);
			}
			return result;
		}
		/*Find Minimum in Rotated Sorted Array 二分法*/
		int findMin(vector<int>& nums)
		{
			//也可以一行代码搞定，直接 return *(min_element(nums.begin(),nums.end()));
			int begin = 0, end = nums.size() - 1;
			if (end == 0) return nums[0];
			if (nums[end] > nums[0]) return nums[0];
			while (begin < end)
			{
				if (begin == end - 1)
					return min(nums[begin], nums[end]);
				int mid = (begin + end) / 2;
				if (nums[mid] < nums[begin])
					end = mid;
				else
					begin = mid;
			}
		}
		/*Find Minimum in Rotated Sorted Array 2 二分法*/
		int findMin2(vector<int>& nums)
		{
			int n = nums.size();
			if (n == 0) return 0;

			int l = 0, r = n - 1;
			while (l <= r)
			{
				if (l == r) return nums[r];
				int mid = (l + r) / 2;

				while (nums[mid] == nums[l] && l<mid) l++;
				while (nums[mid] == nums[r] && r>mid) r--;

				if (nums[mid] > nums[r])
					l = mid + 1;
				else
					r = mid;
			}
		}
		/*Intersection of Two Linked Lists，找两个链表的交点 用Map空间复杂度高*/
		ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
		{
			unordered_map<ListNode*, int> m_map;
			ListNode *head_a = headA, *head_b = headB;
			while (head_a)
			{
				m_map[head_a] = 1;
				head_a = head_a->next;
			}
			while (head_b)
			{
				auto res = m_map.find(head_b);
				if (res != m_map.end())
					return head_b;
				else
					m_map[head_b] = 1;
				head_b = head_b->next;
			}
			return nullptr;
		}
		/*时间复杂度O(N)，空间复杂度O(1)*/
		ListNode *getIntersectionNode_v2(ListNode *headA, ListNode *headB)
		{
			ListNode *head_a = headA, *head_b = headB;
			int lengthA = 0, lengthB = 0;
			while (head_a)
			{
				lengthA++;
				head_a = head_a->next;
			}
			while (head_b)
			{
				lengthB++;
				head_b = head_b->next;
			}
			int diff = abs(lengthA - lengthB); //计算两个链表的长短之差
			int flag = lengthA < lengthB ? 1 : 0;
			while (diff--)
			{
				if (flag)
					headB = headB->next;
				else
					headA = headA->next;
			}
			while (headA && headB)
			{
				if (headA == headB)
					return headA;
				else
				{
					headA = headA->next;
					headB = headB->next;
				}
			}
			return nullptr;
		}
		/*Find Peak Element*/
		int findPeakElement(vector<int>& nums)
		{
			int length = nums.size();
			if (length == 1 || nums[0] > nums[1])
				return 0;
			int i = 0;
			for (i = 1; i < length - 1; i++)
			{
				if (nums[i] > nums[i + 1] && nums[i] > nums[i - 1])
					return i;
			}
			if (nums[i - 1] < nums[i])
				return i;
		}
		/*Compare Version Numbers*/
		int compareVersion(string version1, string version2)
		{
			int i = 0;
			int j = 0;
			int n1 = version1.size();
			int n2 = version2.size();

			int num1 = 0;
			int num2 = 0;
			while (i < n1 || j < n2)
			{
				while (i < n1 && version1[i] != '.'){
					num1 = num1 * 10 + (version1[i] - '0');
					i++;
				}

				while (j<n2 && version2[j] != '.'){
					num2 = num2 * 10 + (version2[j] - '0');;
					j++;
				}

				if (num1>num2) return 1;
				else if (num1 < num2) return -1;

				num1 = 0;
				num2 = 0;
				i++;
				j++;
			}

			return 0;
		}
		/*Maximum gap*/
		int maximumGap(vector<int>& nums)
		{
			sort(nums.begin(), nums.end());
			int max_value = 0;
			for (int i = 1; i < nums.size(); i++)
			{
				max_value = max(max_value, nums[i] - nums[i - 1]);
			}
			return max_value;
		}
		//桶排序
		int maximumGap_v2(vector<int> &nums)
		{
			int n = nums.size();
			if (n < 2) return 0;
			int maxE = *max_element(nums.begin(), nums.end());
			int minE = *min_element(nums.begin(), nums.end());

			int len = maxE - minE;
			if (len <= 1) return len;
			vector<int> buck_max(n, INT_MIN);
			vector<int> buck_min(n, INT_MAX);

			for (int i = 0; i < n; i++)
			{
				// note the divide and multiply order and the double cast
				// it's used to avoid the overflow and underflow during calculation
				int index = (double)(nums[i] - minE) / len * (n - 1);
				buck_max[index] = max(buck_max[index], nums[i]);
				buck_min[index] = min(buck_min[index], nums[i]);
			}

			int gap = 0, pre = buck_max[0];
			for (int i = 1; i < n; i++)
			{
				if (buck_max[i] == INT_MIN) continue;
				gap = max(gap, buck_min[i] - pre);
				pre = buck_max[i];
			}
			return gap;
		}
		/*Excel Sheet Column Title*/
		string convertToTitle(int n)
		{
			string res;
			while (n >= 1)
			{
				res = (char)('A' + (n - 1) % 26) + res;
				n = (n - 1) / 26;
			}
			return res;
		}
		/*Majority Element O(N)时间，O(N)空间*/
		int majorityElement(vector<int>& nums)
		{
			unordered_map<int, int> count;
			int length = nums.size();
			for (int i = 0; i < length; i++)
			{
				auto res = count.find(nums[i]);
				if (res == count.end())
					count[nums[i]] = 1;
				else
					count[nums[i]]++;
				if (count[nums[i]] > length / 2)
					return nums[i];
			}
		}
		/*Moore's voting algorithm 常数空间复杂度*/
		int majorityElement_v2(vector<int>& nums)
		{
			int curValue = 0, curCount = 0;
			for (int i = 0; i < nums.size(); i++)
			{
				if (curCount == 0)
				{
					curCount = 1;
					curValue = nums[i];
				}
				else if (curValue == nums[i])
					curCount++;
				else
					curCount--;
			}
			return curValue;
		}
		/*Majority Element II，，遍历*/
		vector<int> majorityElement2(vector<int>& nums)
		{
			vector<int> result;
			if (nums.size() == 0) return result;
			sort(nums.begin(), nums.end());
			int count = 0, curVal = nums[0];
			for (int i = 0; i < nums.size(); i++)
			{
				if (nums[i] == curVal) count++;
				else
				{
					curVal = nums[i];
					count = 1;
				}
				if (count > nums.size() / 3 && (result.size() == 0 || result[result.size() - 1] != curVal))
					result.push_back(curVal);
			}
			return result;
		}
		/*投票算法*/
		vector<int> majorityElement2_v2(vector<int>& nums) {
			vector<int> v;
			int size = nums.size();
			int n1 = 0, n2 = 0, cn1 = 0, cn2 = 0;
			for (int i = 0; i < size; i++)
			{
				if (nums[i] == n1)
				{
					cn1++;
				}
				else if (nums[i] == n2)
				{
					cn2++;
				}
				else if (cn1 == 0)
				{
					n1 = nums[i];
					cn1 = 1;
				}
				else if (cn2 == 0)
				{
					n2 = nums[i];
					cn2 = 1;
				}
				else
				{
					cn1--;
					cn2--;
				}
			}
			if (cn2 == 0 && size > 0)//用来解决[0 0]的情况
				n2 = nums[0] - 1;
			cn1 = 0;
			cn2 = 0;
			for (int i = 0; i<size; i++)
			{
				if (nums[i] == n1)
					cn1++;
				if (nums[i] == n2)
					cn2++;
			}
			if (cn1>size / 3)
				v.push_back(n1);
			if (cn2 > size / 3)
				v.push_back(n2);
			return v;
		}
		/*Min Stack*/
		class MinStack
		{
		public:
			//int1记录当前节点的值，int2记录到当前节点的最小值
			stack<pair<int, int>> st;
			void push(int x)
			{
				int min_value;
				if (st.empty())
					min_value = x;
				else
					min_value = st.top().second < x ? st.top().second : x;
				pair<int, int> p(x, min_value);
				st.push(p);
			}

			void pop()
			{
				st.pop();
			}

			int top()
			{
				return st.top().first;
			}

			int getMin()
			{
				return st.top().second;
			}
		};
		/*Excel Sheet Column Number*/
		int titleToNumber(string s)
		{
			int length = s.size();
			int result = 0;
			for (int i = 0; i < length; i++)
			{
				result = 26 * result + s[i] - 'A' + 1;
			}
			return result;
		}
		/*Factorial Trailing Zeroes
		n!后缀0的个数 = n!质因子中5的个数 = floor(n/5) + floor(n/25) + floor(n/125) + ....
		*/
		int trailingZeroes(int n)
		{
			int res = 0;
			while (n)
			{
				res += n / 5;
				n /= 5;
			}
			return res;
		}
		long long jiesheng(int n)
		{
			long long  count = 1;
			for (int i = 1; i <= n; i++)
			{
				count *= i;
			}
			return count;
		}
		/*Rotate Array 分成前后两端分别旋转*/
		void rotate(vector<int>& nums, int k)
		{
			int length = nums.size();
			if (k == length) //直接返回
			{
				return;
			}
			else if (k > length) //取余
				k %= length;
			rotate_helper(nums, 0, length - k - 1);
			rotate_helper(nums, length - k, length - 1);
			rotate_helper(nums, 0, length - 1);
		}
		void rotate_helper(vector<int> &nums, int start, int end)
		{
			while (start < end)
			{
				int temp = nums[start];
				nums[start] = nums[end];
				nums[end] = temp;
				start++;
				end--;
			}
		}
		class BSTIterator
		{
		private:
			stack<TreeNode*> s;
		public:
			BSTIterator(TreeNode *root)
			{
				while (root != nullptr)
				{
					s.push(root);
					root = root->left;
				}
			}
			bool hasNext()
			{
				return !s.empty();
			}
			int next()
			{
				if (!hasNext())
				{
					return INT_MIN;
				}
				TreeNode *node = s.top();
				int res = node->val;
				s.pop();
				if (node->right != nullptr)
				{
					node = node->right;
					s.push(node);
					while (node->left != nullptr)
					{
						node = node->left;
						s.push(node);
					}
				}
				return res;
			}
		};
		/*Largest Number*/
		string largestNumber(vector<int>& nums)
		{
			/*定义匿名函数，进行排序*/
			sort(nums.begin(), nums.end(),
				[](const int& l_num, const int& r_num){
				return to_string(l_num) + to_string(r_num) > to_string(r_num) + to_string(l_num);
			});
			if (nums[0] == 0) return "0";
			//累加
			return std::accumulate(nums.begin(), nums.end(), string(""), [](const string& a, int b){return a + to_string(b); });
		}
		/*Repeated DNA Sequences 暴力破解法*/
		vector<string> findRepeatedDnaSequences(string s)
		{
			int i = 0, j = 0;
			int length = s.size();
			vector<string> result;
			for (i = 0; i < length - 20; i++)
			{
				for (j = i + 10; j < length - 10; j++)
				{
					int index = 0;
					while (index < 10 && s[i + index] == s[j + index])
					{
						index++;
					}
					if (index == 10)
					{
						result.push_back(string(s, i, 10));
					}
				}
			}
			return result;
		}
		/*Repeated DNA Sequences 位运算*/
		vector<string> findRepeatedDnaSequences_v2(string s)
		{
			char  hashMap[1048576] = { 0 };
			vector<string> ans;
			int len = s.size(), hashNum = 0;
			if (len < 11) return ans;
			for (int i = 0; i < 9; ++i)
				hashNum = hashNum << 2 | (s[i] - 'A' + 1) % 5;
			for (int i = 9; i < len; ++i)
			if (hashMap[hashNum = (hashNum << 2 | (s[i] - 'A' + 1) % 5) & 0xfffff]++ == 1)
				ans.push_back(s.substr(i - 9, 10));
			return ans;
		}
		/*Repeated DNA Sequences ，unordered_map*/
		vector<string> findRepeatedDnaSequences_v3(string s) {
			unordered_map<string, int> count;
			vector<string> result;
			if (s.size() < 11) return result;
			for (size_t i = 0; i <= s.size() - 10; i++)
			{
				string temp(s, i, 10);
				auto find_res = count.find(temp);
				if (find_res != count.end() && find_res->second == 1)
				{
					result.push_back(temp);
					find_res->second++;
				}
				else
					count[temp]++;
			}
			return result;
		}
		/*Reverse Bits 使用bitset对整数和二进制进行转换*/
		typedef unsigned  int uint32_t;
		uint32_t reverseBits(uint32_t n)
		{
			string s = bitset<32>(n).to_string();
			reverse(s.begin(), s.end());
			return bitset<32>(s).to_ulong();
		}
		/*Reverse Bits 位运算*/
		uint32_t reverseBits_v2(uint32_t n)
		{
			uint32_t res = 0;
			for (int i = 0; i < 32; i++, n >>= 1)
				res = (res << 1) | (n & 1);
			return res;
		}
		/*Number of 1 Bits 位运算*/
		int hammingWeight(uint32_t n)
		{
			int count = 0;
			for (int i = 0; i < 32 && n>0; i++, n >>= 1)
			if (n & 0x1)
				count++;
			return count;
		}
		/*House Robber ，简单动态规划*/
		int rob(vector<int>& nums)
		{
			if (nums.empty())
			{
				return 0;
			}
			else if (nums.size() == 1)
			{
				return nums[0];
			}

			vector<int> dp(nums.size(), 0);
			dp[nums.size() - 1] = nums[nums.size() - 1];
			dp[nums.size() - 2] = max(nums[nums.size() - 2], nums[nums.size() - 1]);

			for (int i = (int)nums.size() - 3; i >= 0; --i)
			{
				dp[i] = max(nums[i] + dp[i + 2],
					dp[i + 1]);
			}

			return dp[0];
		}
		/*House Robber II 动态规划*/
		int rob2(vector<int>& nums)
		{
			if (nums.empty())
			{
				return 0;
			}
			else if (nums.size() == 1)
			{
				return nums[0];
			}
			//不选最后一个节点
			vector<int> temp1(next(nums.begin()), nums.end());
			int value1 = rob2_helper(temp1);
			//不选第一个节点
			vector<int> temp2(nums.begin(), prev(nums.end()));
			int value2 = rob2_helper(temp2);
			return max(value1, value2);

		}
		//求nums的rob value
		int rob2_helper(vector<int> nums)
		{
			if (nums.empty())
			{
				return 0;
			}
			else if (nums.size() == 1)
			{
				return nums[0];
			}

			vector<int> dp(nums.size(), 0);
			dp[nums.size() - 1] = nums[nums.size() - 1];
			dp[nums.size() - 2] = max(nums[nums.size() - 2], nums[nums.size() - 1]);

			for (int i = (int)nums.size() - 3; i >= 0; --i)
			{
				dp[i] = max(nums[i] + dp[i + 2],
					dp[i + 1]);
			}
			return dp[0];
		}
		/*Binary Tree Right Side View 层次遍历*/
		vector<int> rightSideView(TreeNode* root)
		{
			queue<TreeNode*> q1, q2;
			if (root != nullptr)
				q1.push(root);
			vector<int> result;
			while (!q1.empty())
			{
				result.push_back(q1.back()->val);
				while (!q1.empty())
				{
					TreeNode *top = q1.front();
					q1.pop();
					if (top->left)
						q2.push(top->left);
					if (top->right)
						q2.push(top->right);
				}
				swap(q1, q2);
			}
			return result;
		}
		/*Number of Islands,两种方法，并查集，DFS*/
		class numIslandsss
		{
#define MAX 1005
			/* father[x]表示x的父节点 */
			int father[MAX];
			/* rank[x]表示x的秩 */
			int rank[MAX];

			/* 初始化集合 */
			void Make_Set(int x)
			{
				father[x] = x;
				rank[x] = 0;
			}

			/* 查找x元素所在的集合,回溯时压缩路径 */
			int Find_Set(int x)
			{

				if (x != father[x])
				{
					father[x] = Find_Set(father[x]);
				}
				return father[x];
			}

			/* 按秩合并x,y所在的集合 */
			void Union(int x, int y)
			{
				x = Find_Set(x);
				y = Find_Set(y);
				if (x == y) return;
				if (rank[x] > rank[y])
				{
					father[y] = x;
				}
				else
				{
					if (rank[x] == rank[y])
					{
						rank[y]++;
					}
					father[x] = y;
				}
			}
		public:
			/*Number of Islands 并查集*/
			int numIslands(vector<vector<int>>& grid)
			{
				int m = grid.size();
				if (m == 0) return 0;
				int n = grid[0].size();
				for (int i = 0; i < m*n; ++i)
					Make_Set(i);
				for (int i = 0; i < m; i++)
				{
					for (int j = 0; j < n; j++)
					{
						if (grid[i][j] == 1)
						{
							//上
							if (i>0 && grid[i - 1][j] == 1)
								Union(i*n + j, (i - 1)*n + j);
							//左
							if (j>0 && grid[i][j - 1] == 1)
								Union(i*n + j, i*n + j - 1);
						}
					}
				}
				int cnt = 0;
				for (int i = 0; i < m*n; i++)
				{
					if (grid[i / n][i%n] == 1 && father[i] == i)
						cnt++;
				}
				return cnt;
			}
			/*Number of Islands,DFS*/
			int numIslands_dfs(vector<vector<char>>& grid) {
				if (grid.size() == 0) return 0;
				int numIld = 0;
				for (int i = 0; i < grid.size(); ++i){
					for (int j = 0; j < grid[0].size(); ++j){
						if (grid[i][j] == '1'){
							numIld++;
							dfs(i, j, grid);
						}
					}
				}
				return numIld;
			}
			void dfs(int i, int j, vector<vector<char>>& grid){
				if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0') return;
				grid[i][j] = '0';
				dfs(i + 1, j, grid);
				dfs(i, j + 1, grid);
				dfs(i - 1, j, grid);
				dfs(i, j - 1, grid);
			}
		};
		/*
		Bitwise AND of Numbers Range，位运算
		当m!=n，那么最末位必定等0，因为[m,n]必定包含奇偶数，相与最末位等0。当m=n的时候，后面都是0，前面的就是这个范围内的数按位相与的相同部分。
		举例来说：m=4(0000 0100), n=6(0000 0110), 那么范围[4,6]中包含4、5、6，即0000 0100, 0000 0101, 0000 0110，所有的结果按位与得到0000 0100。
		初始：m!=n，于是m,n分别右移一位得到0000 0010, 0000 0011，同时偏移量offset+1；
		m!=n，于是m,n继续右移一位得到0000 0001, 0000 0001，同时偏移量offset+1；
		m=n，得到结果m<<offset。
		*/
		int rangeBitwiseAnd(int m, int n)
		{
			int res = 0;
			int offset = 0;
			while (m != n){
				m >>= 1;
				n >>= 1;
				offset++;
			}
			return m << offset;
		}
		/*Happy Number*/
		bool isHappy(int n)
		{
			unordered_set<int> set;
			while (n != 1)
			{
				int res = 0;
				while (n)
				{
					int a = n % 10;
					res += a*a;
					n /= 10;
				}
				n = res;
				auto find_res = set.find(n);
				if (find_res != set.end())
					return false;
				else
					set.insert(n);
				cout << n << endl;
			}
			return true;
		}
		/*Remove Linked List Elements*/
		ListNode* removeElements(ListNode* head, int val)
		{
			ListNode m_head(-1);
			m_head.next = head;
			ListNode *prev = &m_head;
			ListNode *cur = head;
			while (cur)
			{
				if (cur->val == val)
				{
					prev->next = cur->next;
					cur = prev->next;
				}
				else
				{
					prev = cur;
					cur = cur->next;
				}
			}
			return m_head.next;
		}
		/*
		Delete Node in a Linked List
		这道题让我们删除链表的一个节点，更通常不同的是，没有给我们链表的起点，只给我们了一个要删的节点，
		跟我们以前遇到的情况不太一样，我们之前要删除一个节点的方法是要有其前一个节点的位置，然后将其前一个节点的next连向要删节点的下一个，然后delete掉要删的节点即可。
		这道题的处理方法是先把当前节点的值用下一个节点的值覆盖了，然后我们删除下一个节点即可，代码如下：
		*/
		void deleteNode(ListNode* node)
		{
			node->val = node->next->val;
			ListNode* temp = node->next;
			node->next = node->next->next;
			delete temp;
		}
		/*Count Primes*/
		int countPrimes(int n)
		{
			if (n <= 2)
				return 0;

			bool *prime = new bool[n];
			int i, j, k;

			for (i = 0; i < n; i++)
				prime[i] = true;

			for (i = 2; i < n; i++)
			{
				if (prime[i] == true)
				{
					for (j = i; j + i < n; j += i)
						prime[j + i] = false;
				}
			}
			for (i = 2, k = 0; i < n; i++)
			{
				if (prime[i])
					k++;
			}
			return k;
		}
		/*Isomorphic Strings 分别记录s到t,t到s的单词映射,用hash，32ms*/
		bool isIsomorphic(string s, string t) 
		{
			if (s.length() != t.length()) return false;
			//记录s到t的映射
			unordered_map<char, char> mp;
			for (int i = 0; i < s.length(); ++i) 
			{
				if (mp.find(s[i]) == mp.end())
					mp[s[i]] = t[i];
				else if (mp[s[i]] != t[i]) 
					return false;
			}
			//记录t到s的映射
			mp.clear();
			for (int i = 0; i < s.length(); ++i)
			{
				if (mp.find(t[i]) == mp.end()) 
					mp[t[i]] = s[i];
				else if (mp[t[i]] != s[i]) 
					return false;
			}
			return true;
		}
		/*Isomorphic Strings 分别记录s到t,t到s的单词映射,用数组，8ms*/
		bool isIsomorphic_v2(string s, string t)
		{
			if (s.length() != t.length())
				return false;
			int map1[256], map2[256];
			fill_n(map1, 256, 0);
			fill_n(map2, 256, 0);
			for (int i = 0; i < s.length();i++)
			{
				//s到t的映射检查
				if (map1[s[i]] == 0)
					map1[s[i]] = t[i];
				else if (map1[s[i]] != t[i])
					return false;
				//t到s的映射检查
				if (map2[t[i]] == 0)
					map2[t[i]] = s[i];
				else if (map2[t[i]] != s[i])
					return false;
			}
			return true;
		}
		/*Reverse Linked List 逆转链表，用栈,时间复杂度O(N)，空间复杂度O(N)*/
		ListNode* reverseList(ListNode* head)
		{
			if (head == nullptr)
				return head;
			stack<ListNode*> node_stack;
			while (head)
			{
				node_stack.push(head);
				head = head->next;
			}
			ListNode *myhead = node_stack.top();
			head = myhead;
			node_stack.pop();
			while (!node_stack.empty())
			{
				ListNode * node = node_stack.top();
				node_stack.pop();
				head->next = node;
				head = head->next;
			}
			head->next = nullptr;
			return myhead;
		}
		/*Reverse Linked List 逆转链表，遍历，时间复杂度O(N)，空间复杂度O(1)*/
		ListNode* reverseListv2(ListNode* head)
		{
			ListNode *pos = nullptr,*cur = nullptr;
			if (head && head->next)
			{
				pos = head->next->next;
				cur = head->next;
				head->next->next = head;
				head->next = nullptr;
				head = cur;
				cur = pos;
			}
			else
				return head;
			while (head && cur)
			{
				pos = cur->next;
				cur->next = head;
				head = cur;
				cur = pos;

			}
			return head;
		}
		/*Course Schedule,拓扑排序,来自 https://leetcode.com/discuss/34791/bfs-topological-sort-and-dfs-finding-cycle-by-c */
		bool canFinish_Topological(int numCourses, vector<vector<int>>& prerequisites)
		{
			vector<unordered_set<int>> matrix(numCourses); // save this directed graph
			for (int i = 0; i < prerequisites.size(); ++i)
				matrix[prerequisites[i][1]].insert(prerequisites[i][0]);

			vector<int> d(numCourses, 0); // in-degree
			for (int i = 0; i < numCourses; ++i)
			for (auto it = matrix[i].begin(); it != matrix[i].end(); ++it)
				++d[*it];

			for (int j = 0, i; j < numCourses; ++j)
			{
				for (i = 0; i < numCourses && d[i] != 0; ++i); // find a node whose in-degree is 0

				if (i == numCourses) // if not find
					return false;

				d[i] = -1;
				for (auto it = matrix[i].begin(); it != matrix[i].end(); ++it)
					--d[*it];
			}

			return true;
		}
		/*Course Schedule, dfs*/
		bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
		{
			vector<unordered_set<int>> matrix(numCourses); // 存储有向图
			for (int i = 0; i < prerequisites.size(); ++i)
				matrix[prerequisites[i].second].insert(prerequisites[i].first);

			unordered_set<int> visited; //标记节点是否依赖其他节点
			vector<bool> flag(numCourses, false); //标记节点是否被访问，因为该图存在若干独立子图
			for (int i = 0; i < numCourses; ++i)
				if (!flag[i])
					if (canFinish_DFS(matrix, visited, i, flag))
						return false;
			return true;
		}
		bool canFinish_DFS(vector<unordered_set<int>> &matrix, unordered_set<int> &visited, int b, vector<bool> &flag)
		{
			flag[b] = true;
			visited.insert(b);
			for (auto it = matrix[b].begin(); it != matrix[b].end(); ++it) //dfs访问依赖
			if (visited.find(*it) != visited.end() || canFinish_DFS(matrix, visited, *it, flag))
				return true;
			visited.erase(b);
			return false;
		}
		/*直接dfs会超时，要先把无向图用vector存储*/
		bool canFinish_v2(int numCourses, vector<pair<int, int>>& prerequisites)
		{
			vector<bool> vec_flag(numCourses, false);
			vector<bool> vec_visited(numCourses, false);
			if (numCourses == 0 || numCourses == 1)
				return true;
			for (int i = 0; i < numCourses; ++i)
			if (!vec_visited[i])
			if (!canFinish_dfs_v2(numCourses, prerequisites, vec_flag,i,vec_visited))
					return false;
			return true;
		}
		bool canFinish_dfs_v2(int numCourses, vector<pair<int, int>>& prerequisites, vector<bool>& flags, int start,vector<bool> &visited)
		{
			visited[start] = true;
			flags[start] = true;
			/*循环遍历会导致超时*/
			for (auto iter = prerequisites.begin(); iter != prerequisites.end(); iter++)
			{
				pair<int, int> var = *iter;
				if (var.first == start && flags[var.second] == true)
					return false;
				else if (var.first == start && flags[var.second] == false)
				{
					if (!canFinish_dfs_v2(numCourses, prerequisites, flags, var.second,visited))
						return false;
				}
			}
			flags[start] = false;
			return true;
		}
		/*Course Schedule,拓扑排序*/
		bool canFinish_Top(int numCourses, vector<pair<int,int>>& prerequisites)
		{
			vector<int> in_degree(numCourses,0); //存储入度
			vector<unordered_set<int>> matrix(numCourses);//存储图
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
					}
				}
			}
			if (count == numCourses)
				return true;
			else
				return false;
		}
		/*字典树的实现*/
		class TrieNode {
		public:
			int path;
			int end;
			unordered_map<int,TrieNode*> map;
			// Initialize your data structure here.
			TrieNode() {
				path = 0;
				end = 0;
			}
		};

		class Trie {
		public:
			Trie() {
				root = new TrieNode();
			}

			// Inserts a word into the trie.
			void insert(string word) {
				if (word == "")
					return;
				TrieNode *node = root;
				int index = 0;
				for (int i = 0; i < word.length(); i++)
				{
					index = word[i] - 'a';
					if (node->map.find(index) == node->map.end())
					{
						node->map[index] = new TrieNode();
					}
					node = node->map[index];
					node->path++;
				}
				node->end++;
			}

			// Returns if the word is in the trie.
			bool search(string word) {
				if (word == "")
					return false;
				TrieNode *node = root;
				int index = 0;
				for (int i = 0; i < word.length(); i++)
				{
					index = word[i] - 'a';
					if (node->map.find(index) == node->map.end())
					{
						return false;
					}
					node = node->map[index];
				}
				return node->end != 0;
			}

			// Returns if there is any word in the trie
			// that starts with the given prefix.
			bool startsWith(string prefix) {
				if (prefix == "")
					return false;
				TrieNode *node = root;
				int index = 0;
				for (int i = 0; i < prefix.length(); i++)
				{
					index = prefix[i] - 'a';
					if (node->map.find(index)==node->map.end())
					{
						return false;
					}
					node = node->map[index];
				}
				return node->path;
			}

		private:
			TrieNode* root;
		};
		/*Minimum Size Subarray Sum*/
		int minSubArrayLen(int s, vector<int>& nums)
		{
			int length = nums.size();
			int min_length = length;
			int index1 = 0, index2 = 0;
			int sum = 0;
			while (sum < s && index2<length)
			{
				sum += nums[index2];
				index2++;
			}
			if (index2 == length && sum<s) return 0;
			index2--;
			min_length = index2+1; //初始化最小长度，数组头部
			while (index2 < length)
			{
				while (sum>=s) //压缩数组
					sum -= nums[index1++]; 
				min_length = min(min_length, index2 - index1+2);//更新最小长度
				index2++;
				if (index2<length) //index2++
					sum += nums[index2];
			}
			return min_length;
		}
		/*Add and Search Word，遍历匹配，超时*/
		class WordDictionary {
		public:

			vector<string> words;

			// Adds a word into the data structure.
			void addWord(string word) {
				words.push_back(word);
			}

			// Returns if the word is in the data structure. A word could
			// contain the dot character '.' to represent any one letter.
			bool search(string word) {
				for (auto it = words.begin(); it != words.end(); it++)
				{
					if (match(*it, word))
						return true;
				}
				return false;
			}
			bool match(string dst, string src)
			{
				if (dst.length() != src.length())
					return false;
				int count_dot = 0;
				for (int i = 0; i < src.length(); i++)
				{
					if (src[i] == '.')
					{
						count_dot++;
						if (count_dot>2)
							return false;
					}
					else if (src[i] != dst[i])
						return false;
					else
						count_dot = 0;
				}
				return true;
			}
		};
		/*Add and Search Word ，字典树*/
		class WordDictionary_v2 {
		public:
			struct Node {
				bool end;
				Node *nodes[26];
				Node() {
					end = false;
					memset(nodes, 0, 26 * sizeof(Node*));
				}
			} *root;

			WordDictionary_v2() {
				root = new Node(), root->end = true;
			}

			void addWord(string word) {
				Node *cur = root;
				for (char c : word) {
					Node*& n = cur->nodes[c - 'a'];//watch out,the "&"
					cur = n ? n : (n = new Node());
				}
				cur->end = true;
			}

			bool search(string word) {
				return find(word, 0, root);
			}

			//dfs匹配
			bool find(string& word, int pos, Node *from) {
				if (pos == word.length())
					return from->end;

				if (word[pos] == '.')
					for (auto& n : from->nodes)
						if (n && find(word, pos + 1, n))
							return true;
				else
					return from->nodes[word[pos] - 'a'] ? find(word, pos + 1, from->nodes[word[pos] - 'a']) : false;

				return false;
			}
		};
		class solution_findwords
		{
		public:
			struct Node {
				bool end;
				Node*next[26];
				Node() { end = false; memset(next, 0, 26 * sizeof(Node*)); }
			};

			/*Word Search II,直接dfs遍历会导致超时*/
			vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
			{

				// 构造字典树
				Node *root = new Node();
				for (string w : words) {
					Node *cur = root;
					for (char c : w)
						cur = cur->next[c - 'a'] ? cur->next[c - 'a'] : cur->next[c - 'a'] = new Node();
					cur->end = true;//单词结束标记
				}

				//构造标记
				vector<vector<bool>> flag(board.size(), vector<bool>(board[0].size(), false));
				vector<string> res;

				for(int j = 0; j < board.size(); j++)
				{
					for (int i = 0; i < board[0].size(); i++)
					{
						if (root->next[board[j][i] - 'a'])
							//to do dfs
							findWords_dfs(board, root->next[board[j][i] - 'a'], flag, j, i, res, "");
					}
				}
				//按字典排序
				sort(res.begin(), res.end());
				return res;
			}
			bool findWords_dfs(vector<vector<char>>& board, Node* node, vector<vector<bool>> & flag, int index_x, int index_y,vector<string> &res,string cur_word)
			{
				cur_word += board[index_x][index_y];
				if (node->end)
				{
					auto it = find(res.begin(), res.end(), cur_word);
					if (it == res.end())
						res.push_back(cur_word);
				}

				flag[index_x][index_y] = true;
				//上
				if (index_x > 0 && flag[index_x - 1][index_y] == false && node->next[board[index_x-1][index_y]-'a'] != NULL)
				{
					findWords_dfs(board, node->next[board[index_x - 1][index_y] - 'a'], flag, index_x - 1, index_y, res, cur_word);
				}
				//下
				if (index_x < board.size() - 1 && flag[index_x + 1][index_y] == false && node->next[board[index_x + 1][index_y] - 'a'] != NULL)
				{
					findWords_dfs(board, node->next[board[index_x + 1][index_y] - 'a'], flag, index_x + 1, index_y, res, cur_word);
				}
				//左
				if (index_y>0 && flag[index_x][index_y - 1] == false && node->next[board[index_x][index_y -1] - 'a'] != NULL)
				{
					findWords_dfs(board, node->next[board[index_x][index_y -1 ] - 'a'], flag, index_x , index_y -1, res, cur_word);
				}
				//右
				if (index_y < board[0].size() - 1 && flag[index_x][index_y + 1] == false && node->next[board[index_x][index_y + 1] - 'a'] != NULL)
				{
					findWords_dfs(board, node->next[board[index_x][index_y + 1] - 'a'], flag, index_x, index_y + 1, res, cur_word);
				}
				//取消标记
				flag[index_x][index_y] = false;
				return false;
			}
		};
		/*Word Search II,字典树，来自https://leetcode.com/discuss/69791/30-line-fast-trie-tree-dfs-c-with-comments*/
		class findWords_Solution {
		public:
			struct Node {
				bool end;
				Node*next[26];
				Node() { end = false; memset(next, 0, 26 * sizeof(Node*)); }
			};

			int *dx, *dy, m, n;
			findWords_Solution() {
				dx = new int[4] {0, 1, 0, -1};
				dy = new int[4] {1, 0, -1, 0};
			}

			vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
				m = board.size(), n = board[0].size();

				// construct trie tree
				Node *root = new Node();
				for (string w : words) {
					Node *cur = root;
					for (char c : w)
						cur = cur->next[c - 'a'] ? cur->next[c - 'a'] : cur->next[c - 'a'] = new Node(), cur->end = true;
				}

				// dfs search
				unordered_set<string> ans;
				for (int j = 0; j < m; j++)
				for (int i = 0; i < n; i++)
				if (root->next[board[j][i] - 'a'])
					dfs(board, j, i, root->next[board[j][i] - 'a'], "", ans);

				vector<string> ret(ans.begin(), ans.end());
				return ret;
			}

			void dfs(vector<vector<char>>& board, int y, int x, Node *node, string curString, unordered_set<string>& ans) {
				curString += board[y][x];
				board[y][x] -= 27; // mark it as used

				if (node->end && ans.find(curString) == ans.end())
					ans.insert(curString);

				for (int i = 0; i < 4; i++) {
					int xx = x + dx[i], yy = y + dy[i];
					if (0 <= yy && yy < m && 0 <= xx && xx < n && board[yy][xx] >= 'a' && node->next[board[yy][xx] - 'a'] != NULL)
						dfs(board, yy, xx, node->next[board[yy][xx] - 'a'], curString, ans);
				}
				board[y][x] += 27; // mark it as un-used
			}

		};
	};
}

#if 0
int main()
{
	panzg_leetcode::Solution sol;
	ListNode node1(1);
	ListNode node2(2);
	ListNode node3(3);
	ListNode node4(4);
	ListNode node5(5);
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	//	node4.next = &node5;
	vector<vector<int>> vec(1, vector<int>(2, 3));
	vector<int> nums = { 1,2,3,4,5};
	string s = "AAAAAAAAAAA";
	//sol.reorderList(&node1);
	//ListNode *p = &node1;
	/*auto p = sol.reverseListv2(&node1);
	while (p)
	{
		cout << p->val << endl;
		p = p->next;
	}*/

	vector<vector<char>> board = {
		{'o', 'a', 'a', 'n' },
		{ 'e', 't', 'a', 'e' },
		{ 'i', 'h', 'k', 'r' },
		{ 'i', 'f', 'l', 'v' }
	};
	vector<string> words = { "oath", "pea", "eat", "rain" };
	panzg_leetcode::Solution::solution_findwords sol1;
	auto res = sol1.findWords(board, words);
	
	//panzg_leetcode::Solution::findWords_Solution sol2;
	/*auto res = sol2.findWords(board, words);
	
	}*/
	for each (auto var in res)
	{
		cout << var << endl;
	}
	/*for each (auto var in res)
	{
	cout << var << endl;
	}*/


	//cout << std::numeric_limits<short>::max();

	system("pause");
}

#endif