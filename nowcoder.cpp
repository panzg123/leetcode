#include"header.h"
using namespace std;
namespace nowcoder{
	class Solution{
	public:
		void Print(){
			cout << "hello nowcoder" << endl;
		}
		//华为机试，分割字符串
		void wordSplit()
		{
			string str;
			while (cin >> str)
			{
				if (str.length() <= 8)
				{
					str += string(8 - str.length(), '0');
					cout << str<<endl;
				}
				else
				{
					int index = 0;
					while (index+7 < str.length())
					{
						string str_temp(str, index, 8);
						cout << str_temp << endl;
						index += 8;
					}
					if (index < str.length())
					{
						string str_temp(str, index, str.length() - index);
						str_temp += string(8 + index - str.length(), '0');
						cout << str_temp << endl;
					}
				}
			}
		}
		//华为机试，进制转换
		void convertHex2Dec()
		{
			string str;
			while (cin>>str)
			{
				stringstream ss(str);
				string hex_str;
				while (ss >> hex_str)
				{
					//十六进制转换为10进制
					int dec_number = stoi(hex_str, nullptr, 16);
					cout << dec_number << " ";
				}
				cout << endl;
			}
		}
		//华为机试，合并序列
		void merge_array(){
			int number;
			while (cin >> number)
			{
				unordered_map<int, int> map;
				int key, value;
				for (int i = 0; i < number; i++){
					cin >> key >> value;
					map[key] += value;
				}
				for (auto item : map){
					cout << item.first << " " << item.second << endl;
				}
			}
		}
		void charcount()
		{
			string str;
			vector<int> flag(128, 0);
			getline(cin, str);
			int ret_count = 0;
			for (int i = 0; i < str.length(); i++){
				if (str[i] < 128 && flag[str[i]] == 0){
					ret_count++;
					flag[str[i]] = 1;
				}
			}
			cout << ret_count << endl;
		}
		void check1number()
		{
			int number;
			cin >> number;
			int ret = 0;
			while (number){
				ret++;
				number = number&(number - 1);
			}
			cout << ret << endl;
		}
		//华为机试，判断是否是合格的密码
		bool isValidPasswd(string str)
		{
			if (str.length() <= 8)
				return false;
			vector<int> flag(4, 0);
			int count = 0;
			for (int i = 0; i < str.length();i++)
			{
				if (isupper(str[i]) && flag[0] == 0)
				{
					count++;
					flag[0] = 1;
				}
				else if (islower(str[i]) && flag[1]==0)
				{
					count++;
					flag[1] = 1;
				}
				else if (isdigit(str[i]) && flag[2] == 0)
				{
					count++;
					flag[2] = 1;
				}
				else if (!(isdigit(str[i])||islower(str[i])||isupper(str[i]))&&flag[3]==0)
				{
					count++;
					flag[3] = 1;
				}
			}
			if (count < 3)
				return false;
			for (int i = 0; i < str.length() - 3;i++)
			{
				string temp(str, i, 3);
				auto pos = str.rfind(temp);
				if (pos != i)
					return false;
			}
			return true;
		}
		//剑指offer，二维数组的查找
		//思路：从左下角遍历，因为以此元素为标准，右边的元素比它大，上面的比它小
		bool Find(vector<vector<int> > array, int target) 
		{
			int rows = array.size();
			int cols = array[0].size();
			int x_pos = rows - 1;
			int y_pos = 0;
			while (x_pos>=0 && y_pos<cols)
			{
				if (array[x_pos][y_pos] == target)
					return true;
				else if (array[x_pos][y_pos] < target)
					y_pos += 1;
				else
					x_pos -= 1;
			}
			return false;
		}
		//二分查找
		bool binary_search(vector<int> nums, int target)
		{
			int low = 0;
			int high = nums.size() - 1;
			while (low <= high)
			{
				int middle = (high - low) / 2 + low;
				if (nums[middle] == target)
					return true;
				else if (nums[middle] > target)
					high = middle - 1;
				else
					low = middle + 1;
			}
			return false;
		}
		//剑指offer，替换空格
		void replaceSpace(char *str, int length)
		{
			int blank_count = 0;
			int idx = 0;
			int old_len = 0;
			//统计空格个数
			while (str[idx]!='\0')
			{
				if (str[idx] == ' ')
					blank_count++;
				old_len++;
				idx++;
			}
			//计算替换后的字符串长度
			int new_len = old_len + blank_count * 2;
			if (new_len > length)
				return;
			int idx_old = old_len;
			int idx_new = new_len;
			//从后往前替换空格f
			while (idx_old>=0 && idx_new>idx_old)
			{
				if (str[idx_old] == ' ')
				{
					str[idx_new--] = '0';
					str[idx_new--] = '2';
					str[idx_new--] = '%';
				}
				else
					str[idx_new--] = str[idx_old];
				idx_old--;
			}
		}
		//jianzhioffer，重建二叉树，用前序和中序
		TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in) 
		{
			TreeNode *root = new TreeNode(pre[0]);
			if (pre.size() == 1)
			{
				return root;
			}
			auto pos = std::find(in.begin(), in.end(), pre[0]);
			int len = 0;
			//左子树
			if (len = distance(in.begin(),pos))
			{
				vector<int> subpre(next(pre.begin()), pre.begin() + len + 1);
				vector<int> subin(in.begin(), pos);
				root->left = reConstructBinaryTree(subpre, subin);
			}
			//右子树
			len = distance(pos, in.end()) - 1;
			if (len > 0)
			{
				vector<int> subpre(pre.end() - len, pre.end());
				vector<int> subin(pos + 1, in.end());
				root->right = reConstructBinaryTree(subpre, subin);
			}
			return root;
		}
		//递归实现快速排序
		void QSort(vector<int> &nums,int start,int end)
		{
			int partition_idx = start;//分割点
			int low = start;
			int high = end;
			int temp = nums[partition_idx];
			while (low < high)
			{
				while (low < high && nums[high] >= temp)
					high--;
				if (low < high)
				{
					nums[low] = nums[high];
					low++;
				}
				while (low < high && nums[low] <= temp)
					low++;
				if (low < high)
				{
					nums[high] = nums[low];
					high--;
				}
			}
			nums[low] = temp;
			if (start < low)
				QSort(nums, start, low - 1);
			if (end > low)
				QSort(nums, low + 1, end);
		}
		//插入排序
		void insertSort(vector<int>&nums)
		{
			int len = nums.size();
			for (int i = 1; i < len;i++)
			{
				int temp = nums[i];
				int insert_pos = i - 1;
				while (insert_pos >= 0 && nums[insert_pos] > temp)
				{
					nums[insert_pos + 1] = nums[insert_pos];
					insert_pos--;
				}
				nums[insert_pos+1] = temp;
			}
		}
		//冒泡排序
		void BubleSort(vector<int> &nums)
		{
			int len = nums.size();
			int flag = 1;
			for (int i = 1; i < len && flag==1;i++)
			{
				flag = 0;
				for (int j = 0; j < len - i;j++)
				{
					if (nums[j] > nums[j + 1])
					{
						flag = 1;
						swap(nums[j], nums[j + 1]);
					}
				}
			}
		}
		void MergeSortHelper(vector<int> &nums, int step, vector<int>& swap_data)
		{
			int left_low = 0, left_high;
			int right_low, right_high;
			int idx = 0;
			int len = nums.size();
			int i, j;
			while (left_low + step < len)
			{
				right_low = left_low + step;
				left_high = right_low - 1;
				right_high = right_low + step - 1 < len ? right_low + step - 1 : len - 1;
				//合并两个子序列
				for (i = left_low, j = right_low; i <= left_high && j <= right_high; idx++)
				{
					if (nums[i] < nums[j])
						swap_data[idx] = nums[i++];
					else
						swap_data[idx] = nums[j++];
				}
				while (i <= left_high)
					swap_data[idx++] = nums[i++];
				while (j <= right_high)
					swap_data[idx++] = nums[j++];
				left_low = right_high + 1;
			}
			for (i = left_low; i < len;)
				swap_data[idx++] = nums[i++];
		}
		//归并排序，非递归
		void MergeSort(vector<int>& nums)
		{
			int i, step = 1;
			vector<int> swap_data;
			swap_data.resize(nums.size());
			while (step < nums.size())
			{
				MergeSortHelper(nums, step, swap_data);
				for (int i = 0; i < nums.size(); i++)
					nums[i] = swap_data[i];
				step *= 2;
			}
		}
		//剑指offer，斐波那契数列
		int Fibonacci(int n) 
		{
			if (n == 0)
				return 0;
			if (n == 1)
				return 1;
			int pre = 0;
			int cur = 1;
			int index = 2;
			int temp=0;
			while (index++ <= n)
			{
				temp = cur + pre;
				pre = cur;
				cur = temp;
			}
			return cur;
		}
		//剑指offer，跳台阶2
		int jumpFloorII(int number)
		{
			if (number == 0 || number == 1)
				return 1;
			return pow(2, number-1);
		}
		//剑指offer，二进数中1的个数
		int  NumberOf1(int n) 
		{
			int count = 0;
			while (n)
			{
				n &= (n - 1);
				count++;
			}
			return count;
		}
		//剑指offer，数值的整数次方
		double Power(double base, int exponent) 
		{
			if (exponent == 0)
				return 1;
			int neg = 0;
			if (exponent < 0)
			{
				exponent = 0 - exponent;
				neg = 1;
			}
			double ret = 1;
			ret = Power(base, exponent / 2)*Power(base, exponent / 2);
			if (exponent % 2 == 1)
				ret *= base;
			if (neg)
				return 1 / ret;
			else
				return ret;
		}
		//剑指offer，调整数组顺序使奇数位于偶数前面
		void reOrderArray(vector<int> &array) 
		{
			vector<int> odd;//奇数
			vector<int> even;//偶数
			for (auto i : array){
				if (i % 2 == 1)
					odd.push_back(i);
				else
					even.push_back(i);
			}
			array = odd;
			for (auto num : even)
				array.push_back(num);
		}
		//剑指offer，链表中倒数第k个结点
		ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
			ListNode* far_head = pListHead;
			unsigned int step = 0;
			while (far_head != NULL && step < k){
				far_head = far_head->next;
				step++;
			}
			if (step != k)
				return NULL;
			while (pListHead && far_head){
				pListHead = pListHead->next;
				far_head = far_head->next;
			}
			return pListHead;
		}
		//剑指offer，反转链表
		ListNode* ReverseList(ListNode* pHead)
		{
			ListNode* pre = NULL;
			ListNode* cur = pHead;
			while (pHead)
			{
				cur = pHead;
				pHead = pHead->next;
				cur->next = pre;
				pre = cur;
			}
			return cur;
		}
		//剑指offer，合并两个有序链表
		ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
		{
			ListNode ret_head(-1);
			ListNode* head = &ret_head;
			while(pHead1 != NULL && pHead2 != NULL)
			{
				if (pHead1->val < pHead2->val){
					head->next = pHead1;
					head = head->next;
					pHead1 = pHead1->next;
				}
				else{
					head->next = pHead2;
					head = head->next;
					pHead2 = pHead2->next;
				}
			}
			while (pHead1)
			{
				head->next = pHead1;
				head = head->next;
				pHead1 = pHead1->next;
			}
			while (pHead2)
			{
				head->next = pHead2;
				head = head->next;
				pHead2 = pHead2->next;
			}
			return ret_head.next;
		}
		bool isSubtree(TreeNode* pRootA, TreeNode* pRootB) 
		{
			if (pRootB == NULL) 
				return true;
			if (pRootA == NULL) 
				return false;
			if (pRootB->val == pRootA->val) 
			{
				return isSubtree(pRootA->left, pRootB->left)
					&& isSubtree(pRootA->right, pRootB->right);
			}
			else 
				return false;
		}
		//剑指offer，判断树的子结构
		bool HasSubtree(TreeNode* pRootA, TreeNode* pRootB)
		{
			if (pRootA == NULL || pRootB == NULL) 
				return false;
			return isSubtree(pRootA, pRootB) ||
				HasSubtree(pRootA->left, pRootB) ||
				HasSubtree(pRootA->right, pRootB);
		}
		//剑指offer，镜像树
		void Mirror(TreeNode *pRoot) 
		{
			if (pRoot == NULL)
				return;
			TreeNode* temp = pRoot->left;
			pRoot->left = pRoot->right;
			pRoot->right = temp;
			Mirror(pRoot->left);
			Mirror(pRoot->right);
		}
		//剑指offer，顺时针打印矩阵
		vector<int> printMatrix(vector<vector<int> > matrix) 
		{
			vector<int> ret;
			int rows = matrix.size();
			int cols = matrix[0].size();
			int pos = 0;
			while (2 * pos <rows && 2 * pos < cols)
			{
				int endX = rows - pos - 1;
				int endY = cols - pos - 1;
				for (int y = pos; y <= endY; y++)
					ret.push_back(matrix[pos][y]);
				if (pos < endX)
					for (int x = pos + 1; x <= endX; x++)
						ret.push_back(matrix[x][endY]);
				if (pos < endX && pos < endY)
					for (int y = endY -1; y >= pos; y--)
						ret.push_back(matrix[endX][y]);
				if (pos < endX - 1 && pos < endY)
					for (int x = endX - 1; x > pos; x--)
						ret.push_back(matrix[x][pos]);
				pos++;
			}
			return ret;
		}
		//剑指offer，实现记录最小值的栈
		class MinStackSolution {
		public:
			stack<int> data;
			stack<int> min_data;
			void push(int value) {
				data.push(value);
				if (min_data.empty())
					min_data.push(value);
				else
				{
					if (min_data.top() < value)
						min_data.push(min_data.top());
					else
						min_data.push(value);
				}
			}
			void pop() {
				data.pop();
				min_data.pop();
			}
			int top() {
				return data.top();
			}
			int min() {
				return min_data.top();
			}
		};
		//剑指offer，栈的压入、弹出序列
		bool IsPopOrder(vector<int> pushV, vector<int> popV) 
		{
			int len = pushV.size();
			if (len == 0)
				return false;
			if (len != popV.size())
				return false;
			stack<int> stack_push;
			int index = 0;
			while (index <= len)
			{
				while (!stack_push.empty() && stack_push.top() == popV.front())
				{
					stack_push.pop();
					popV.erase(popV.begin());
				}
				if (index == len)
					break;
				stack_push.push(pushV[index++]);
			}
			if (stack_push.empty())
				return true;
			else
				return false;
		}
		//剑指offer，从下到下打印二叉树
		vector<int> PrintFromTopToBottom(TreeNode *root)
		{
			vector<int> ret;
			if (root == nullptr)
				return ret;
			queue<TreeNode*> q;
			q.push(root);
			while (!q.empty())
			{
				TreeNode *front = q.front();
				q.pop();
				ret.push_back(front->val);
				if (front->left != nullptr)
					q.push(front->left);
				if (front->right != nullptr)
					q.push(front->right);
			}
			return ret;
		}
		//剑指offer，二叉搜索树的后序遍历序列
		bool VerifySquenceOfBST(vector<int> sequence) 
		{
			if (sequence.size() == 0)
				return false;
			return VerifySquenceOfBST_helper(sequence);
		}
		bool VerifySquenceOfBST_helper(vector<int> sequence)
		{
			int len = sequence.size();
			if (len == 1 || len == 0)
				return true;
			int last_point = sequence.back();
			vector<int>::iterator pos = find_if(sequence.begin(), sequence.end(), bind(greater<int>(), std::placeholders::_1, last_point));
			vector<int>::iterator pos2 = find_if(pos, sequence.end(), bind(less<int>(), std::placeholders::_1, last_point));
			if (pos2 != sequence.end())
				return false;
			vector<int> low(sequence.begin(), pos);
			vector<int> high(pos, sequence.end());
			if (!high.empty())
				high.pop_back();
			else
				low.pop_back();
			return VerifySquenceOfBST_helper(low) && VerifySquenceOfBST_helper(high);
		}

		//二叉树中和为某一值的路径
		vector<vector<int> > FindPath(TreeNode* root, int expectNumber)
		{
			vector<vector<int>> ret;
			vector<int> path;
			if (root == nullptr)
				return ret;
			int curVal = 0;
			FindPathHelper(root, expectNumber, curVal, ret, path);
			return ret;
		}
		void FindPathHelper(TreeNode* root, int expectVal, int curVal, vector<vector<int>> &ret,vector<int> path)
		{
			curVal += root->val;
			path.push_back(root->val);
			bool isLeaf = root->left == nullptr && root->right == nullptr;
			if (curVal == expectVal && isLeaf)
			{
				ret.push_back(path);
			}
			if (curVal > expectVal)
				return;
			if (root->left != nullptr)
				FindPathHelper(root->left, expectVal, curVal, ret, path);
			if (root->right != nullptr)
				FindPathHelper(root->right, expectVal, curVal, ret, path);
		}
	};
}


#if 1
int main(){
	nowcoder::Solution sol;
	vector<vector<int>> nums = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};

	vector<vector<int>> nums2 = { { 1 }, { 2 }, { 3 }, { 4 }, { 5 } };
	vector<int> pre = { 8,7,6,5,4,3,2,1 };
	vector<int> in = { 4, 7, 2, 1, 5, 3, 8, 6 };
	char str[] = "hello world";

	ListNode node1(1);
	ListNode node2(2);
	ListNode node3(3);
	ListNode node4(4);
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;

	ListNode node6(6);
	ListNode node7(7);
	ListNode node8(8);
	ListNode node9(9);
	node6.next = &node7;
	node7.next = &node8;
	node8.next = &node9;


	vector<int> sequence = { 1,2,3,4,5};
	auto ret = sol.VerifySquenceOfBST(sequence);

	std::cout << ret;

	system("pause");
}
#endif