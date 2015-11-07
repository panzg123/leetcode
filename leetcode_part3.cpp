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
				//��
				for (int j = beginX; j <= endX; ++j)
					result.push_back(matrix[beginY][j]);
				if (++beginY > endY)
					break;
				//��
				for (int i = beginY; i <= endY; ++i)
					result.push_back(matrix[i][endX]);
				if (beginX > --endX)
					break;
				//��
				for (int j = endX; j >= beginX; --j)
					result.push_back(matrix[endY][j]);
				if (--endY < beginY)
					break;
				//��
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
		/*ZigZag Conversion ��ѧ����*/
		string convert(string s, int numRows)
		{
			if (numRows <= 1 || s.size() <= 1)
				return s;
			string result;
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0, index = i; index < s.size(); j++, index = (2 * numRows - 2) * j + i)
				{
					result.append(1, s[index]); // ��ֱԪ��
					if (i == 0 || i == numRows - 1)
						continue; // б�Խ�Ԫ��
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
		// ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(1)
		vector<string> fullJustify(vector<string> &words, int L)
		{
			vector<string> result;
			const int n = words.size();
			int begin = 0, len = 0; // ��ǰ�е���㣬��ǰ����
			for (int i = 0; i < n; ++i) {
				if (len + words[i].size() + (i - begin) > L)
				{
					result.push_back(connect(words, begin, i - 1, len, L, false));
					begin = i;
					len = 0;
				}
				len += words[i].size();
			}
			// ���һ�в��� L
			result.push_back(connect(words, begin, n - 1, len, L, true));
			return result;
		}
		/**
		* @brief �� words[begin, end] ����һ��
		* @param[in] words �����б�
		* @param[in] begin ��ʼ
		* @param[in] end ����
		* @param[in] len words[begin, end] ���е��ʼ������ĳ���
		* @param[in] L ��Ŀ�涨��һ�г���
		* @param[in] is_last �Ƿ������һ��
		* @return �����ĵ�ǰ��
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
		* @brief ��ӿո�.
		* @param[inout]s һ��
		* @param[in] i ��ǰ��϶�����
		* @param[in] n ��϶����
		* @param[in] L �ܹ���Ҫ��ӵĿն���
		* @param[in] is_last �Ƿ������һ��
		* @return ��
		*/
		void addSpaces(string &s, int i, int n, int L, bool is_last)
		{
			if (n < 1 || i > n - 1) return;
			int spaces = is_last ? 1 : (L / n + (i < (L % n) ? 1 : 0));
			s.append(spaces, ' ');
		}
		//LeetCode, Max Points on a Line
		// ����ö�ٷ����Ա�Ϊ���ģ�ʱ�临�Ӷ� O(n^3)���ռ临�Ӷ� O(1)
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
		�÷����ĺ����ǽ�ԭ����ת���һ��Ѱ�ҵ�kС�������⣨��������ԭ�����������У���������λ��ʵ�����ǵ�(m+n)/2С����������ֻҪ����˵�kС�������⣬ԭ����Ҳ���Խ����

		���ȼ�������A��B��Ԫ�ظ���������k/2�����ǱȽ�A[k/2-1]��B[k/2-1]����Ԫ�أ�������Ԫ�طֱ��ʾA�ĵ�k/2С��Ԫ�غ�B�ĵ�k/2С��Ԫ�ء�������Ԫ�رȽϹ������������>��<��=�����A[k/2-1]<B[k/2-1]�����ʾA[0]��A[k/2-1]��Ԫ�ض���A��B�ϲ�֮���ǰkС��Ԫ���С����仰˵��A[k/2-1]�����ܴ���������ϲ�֮��ĵ�kСֵ���������ǿ��Խ���������

		֤��Ҳ�ܼ򵥣����Բ��÷�֤��������A[k/2-1]���ںϲ�֮��ĵ�kСֵ�����ǲ����ٶ���Ϊ�ڣ�k+1��Сֵ������A[k/2-1]С��B[k/2-1]������B[k/2-1]�����ǵڣ�k+2��Сֵ����ʵ���ϣ���A���������k/2-1��Ԫ��С��A[k/2-1]��B��Ҳ�������k/2-1��Ԫ��С��A[k/2-1]������С��A[k/2-1]��Ԫ�ظ���������k/2+ k/2-2��С��k������A[k/2-1]�ǵڣ�k+1������ì�ܡ�

		��A[k/2-1]>B[k/2-1]ʱ�������ƵĽ��ۡ�

		��A[k/2-1]=B[k/2-1]ʱ�������Ѿ��ҵ��˵�kС������Ҳ�������ȵ�Ԫ�أ����ǽ����Ϊm��������A��B�зֱ���k/2-1��Ԫ��С��m������m���ǵ�kС������(����������˻������ʣ����kΪ��������m������λ���������ǽ��������뻯���ǣ���ʵ�ʴ��������в�ͬ��������k/2��Ȼ������k-k/2�����һ������)

		ͨ������ķ��������Ǽ����Բ��õݹ�ķ�ʽʵ��Ѱ�ҵ�kС�������������ǻ���Ҫ���Ǽ����߽�������

		���A����BΪ�գ���ֱ�ӷ���B[k-1]����A[k-1]��
		���kΪ1������ֻ��Ҫ����A[0]��B[0]�еĽ�Сֵ��
		���A[k/2-1]=B[k/2-1]����������һ����
		*/
		double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
		{
			int k = nums1.size() + nums2.size();
			//ż��
			if (k % 2 == 0)
				return (
				findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2) +
				findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2 + 1)
				) / 2;
			//����
			else
				return findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2 + 1);
		}
		double findKthSortedArrays(vector<int>::const_iterator nums1, int m, vector<int>::const_iterator nums2, int n, int k)
		{
			if (m > n)
				return findKthSortedArrays(nums2, n, nums1, m, k);
			//�߽�����
			if (m == 0)
				return *(nums2 + k - 1);
			//���ص�1С��ֵ����min(num[0],num1[0])
			if (k == 1)
				return min(*nums1, *nums2);

			//�������ж�B[k-1]��A[k-1]��ϵ��
			int mk = min(m, k / 2);
			int nk = k - mk;
			//���A[k/2-1]=B[k/2-1]����������һ����
			if (*(nums1 + mk - 1) == *(nums2 + nk - 1))
				return *(nums1 + mk - 1);
			//��A[k/2-1] < B[k/2-1],ɾ��A[0��k/2-1]
			else if (*(nums1 + mk - 1) < *(nums2 + nk - 1))
				return findKthSortedArrays(nums1 + mk, m - mk, nums2, n, k - mk);
			//��A[k/2-1] > B[k/2-1],ɾ��B[0��k/2-1]
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
		/*Reverse Nodes in k-Group ʹ��ջ���б���*/
		ListNode* reverseKGroup(ListNode* head, int k)
		{
			stack<ListNode*> stack_node;
			int flag = 0; //�ж��Ƿ�����������ĵ�һ���ڵ�
			ListNode * last_node = nullptr;  //��¼���һ���ڵ�
			ListNode * my_head = nullptr; //��¼�׽ڵ㣬���з���
			ListNode * temp = nullptr; //��ʱ�ڵ�
			int count = 0; //����������ջһ��count++
			while (head)
			{
				//ѹ��k���ڵ�
				while (head && count < k)
				{
					stack_node.push(head);
					head = head->next;
					count++;
				}
				//��������㹻
				if (count == k)
				{
					for (int i = 0; i < k; i++)
					{
						temp = stack_node.top();
						if (!flag) //��һ���ڵ㣬��Ҫ��ֵ��my_head
						{
							flag = 1;
							my_head = temp;
						}
						if (last_node != nullptr)  //����β��
						{
							last_node->next = temp;
						}
						last_node = temp;
						stack_node.pop();
					}
					last_node->next = nullptr;
					count = 0;
				}
				//β����������
				else
				{
					for (int i = 0; i < count; i++)
					{
						temp = stack_node.top();
						stack_node.pop();
					}
					if (!flag) //��һ���ڵ㣬��Ҫ��ֵ��my_head
					{
						flag = 1;
						my_head = temp;
					}
					if (last_node != nullptr)  //����β��
					{
						last_node->next = temp;
					}
				}
			}
			return my_head;
		}
		/*First Missing Positive ʱ�临�ӶȺͿռ临�Ӷȶ���o(n)��������Ҫ��*/
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
		/*first missing positive �ռ临�Ӷ�Ϊ����
		˼·�����԰������е�Ԫ�ط��롰���ʡ���λ��ʱ�����罫1����0λ���ϣ�2����1λ���ϡ����������������飬���ĳ��λ���ϵ��������ʣ��򷵻ظ�λ���ϡ����ʡ�������
		*/
		int firstMissingPositive_v2(vector<int> &nums)
		{
			int size = nums.size();
			if (size == 0) return 1;
			for (int i = 1; i <= size; i++)
			{
				//��Ԫ�ط�����ʵ�λ��
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
		/*Plus One ����������������1*/
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
		/*Symmetric Tree �ݹ�*/
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
		/*Maximum Depth of Binary Tree �ݹ�*/
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
		/*Longest Consecutive Sequence ͵��������O(n)Ҫ��*/
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
		/*Longest Consecutive Sequence,��unordered_set��O(n)*/
		int longestConsecutive(vector<int>& nums)
		{
			int len = 0, candidate, val;
			unordered_set<int> set(nums.begin(), nums.end());
			while (!set.empty())
			{
				val = *set.begin();
				set.erase(val);
				candidate = 1;
				//�����val�����
				for (int i = val + 1; set.find(i) != set.end(); ++i)
				{
					set.erase(i);
					candidate++;
				}
				//�����valС����
				for (int i = val - 1; set.find(i) != set.end(); --i)
				{
					set.erase(i);
					candidate++;
				}
				len = max(len, candidate);
			}
			return len;
		}
		/*Copy List with Random Pointer ʹ��unordered_map,ʱ�临�Ӷȡ��ռ临�Ӷȶ�ΪO(N)*/
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
		/*Reverse Words in a String ��ջ*/
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
		/*Reverse Words in a String �ֲ���ת��Ȼ�����巭ת*/
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
		/*�ַ����ָ��������洢��stack��*/
		stack<std::string> reverseWords_helper(std::string str, std::string pattern)
		{
			std::string::size_type pos;
			std::stack<std::string> result;
			str += pattern;//��չ�ַ����Է������
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
		/*Linked List Cycle,�ж������Ƿ��л�,�������ָ������*/
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
		/*Linked List Cycle 2���һ�����㣬�������ָ������*/
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
		/*Reorder List ��ջ���������¼λ�ã��ռ临�Ӷ��е��*/
		void reorderList(ListNode* head) 
		{
			ListNode *my_head = head;
			vector<ListNode*> node_vec; //��¼ָ��
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
			while (i<j)  //��������
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
					//��itָ���Ԫ���ƶ���lru������ײ�
					lru.splice(lru.begin(), lru, it->second);
					return (*(it->second))->value;
				}
			}
			void set(int key, int value)
			{
				Entry *entry = nullptr;
				auto it = hash.find(key);
				if (it == hash.end()) //������key
				{
					entry = new Entry(key, value);
					if (currentSize >= capacity) //�ռ��þ���ɾ���ײ�Ԫ��
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
					lru.splice(lru.begin(), lru, it->second); //�ƶ����ײ�
				}
			}
		};
	};
}
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
	vector<int> nums = { 3, 2, 1, 2, 3, 4, };

	sol.reorderList(&node1);
	ListNode *p = &node1;
	while (p)
	{
		cout << p->val << endl;
		p = p->next;
	}

	system("pause");
}