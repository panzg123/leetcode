我自己的leetcode刷题记录
=========================
###[20150920]
    Valid Palindrome
    Implement strStr()
    String to Integer (atoi)
    addBinary
    longestPalindrome 
    maximal rectangle :dp问题，较难
    largestRectangleArea 求直方图的最大面积，左右两次扫面+剪枝优化
    Valid Parentheses 用栈判断括号匹配
    Regular Expression Matching 递归匹配
	wildcard matching 动态规划
	longest common prefix , 简单
	valid number, hard, 用有限自动机
	integer to roman ,easy , 模拟
	roman to integer ,easy , 模拟
	count and say , easy , 模拟
	Anagrams 字符串处理,map
	Simplify Path,字符串处理，stack
	Length of Last Word，字符串处理.细节题
	Reverse Polish Number,栈
	Binary Tree Preorder Traversal,树的先序遍历，递归，栈，morris遍历
	Binary Tree Inorder Traversal ，中序遍历，递归，栈，morris遍历
	Binary Tree Postorder Traversal，后序遍历。递归，栈，morris遍历
	Binary Tree Level Order Traversal，层次遍历，递归
	Binary Tree Zigzag Level Order Traversal，层次遍历，递归+反转
	Recover Binary Search Tree，搜索二叉树，递归
	Same Tree，判断是否是相同的树，递归或者迭代
	Symmetric Tree，对称树。递归或者迭代
	Balanced Binary Tree，判断是否是平衡二叉树，递归
	Flatten Binary Tree to Linked List，
	Populating Next Right Pointers in Each Node II
	Construct Binary Tree from Preorder and Inorder Traversal，用先序和中序遍历构建二叉树，递归
	Construct Binary Tree from Inorder and Postorder Traversal，用中序和后序遍历构建二叉树，递归
	Unique Binary Search Trees 动态规划
	Unique Binary Search Trees II 求给定n的所有可能的搜索二叉树组合。 递归
	Validate Binary Search Tree，判断是否是搜索二叉树，递归
	Convert Sorted List to Binary Search Tree，自底向上,时间复杂度 O(n)，空间复杂度 O(logn)
	Minimum Depth of Binary Tree,二叉树的递归
	Maximum Depth of Binary Tree，二叉树的递归
	Path Sum，二叉树的递归，求根到叶子节点的路径之和等于给定的数字。
	Path Sum II，二叉树的递归，求所有的路径。
	Binary Tree Maximum Path Sum，递归会超时，用dfs。
	Populating Next Right Pointers in Each Node，兄弟节点的链接
	Sum Root to Leaf Numbers，计算所有根到叶子路径的和。
	Merge Sorted Array,合并已排序的两个数组
	Merge Two Sorted Lists，合并两个已排序的链表
	Merge k Sorted Lists，合并k个已排序的链表
	Sort List,对链表进行排序，常数空间且 O(nlogn)，单链表适合用归并排序，双向链表适合用快速排序。
	Sort Colors，双指针，计数
	Search for a Range，查询范围，stl，Low_bound,upper_bound
	Search Insert Position,新元素插入位置查询，stl-->low_bound
	Search a 2D Matrix,矩阵元素位置查询，二分查找
	Search a 2D Matrix II，矩阵元素位置查询
	Subsets，递归，全组合
	Subsets II，不重复组合
	Permutations，全排列，stl-->next_premutation或者递归
	Permutations II，有重复数据的全排列，stl->next_premutation或者递归
	Combinations，递归
	Letter Combinations of a Phone Number，递归
	
	Updating....
    
###[2015-10-22]
	Spiral Matrix,模拟题，细节实现
	Spiral Matrix 2 模拟题
	Divide Two Integers,模拟题，用减法实现除法，注意溢出
	LeetCode, Text Justification,时间复杂度 O(n)，空间复杂度 O(1)
	Max Points on a Line，暴力枚举法，以边为中心，时间复杂度 O(n^3)，空间复杂度 O(1)
###[2015-10-28]
	Median of Two Sorted Arrays,求两个已排序数组中的中位数，hard.
	Swap Nodes in Pairs,链表，节点交换
	Reverse Nodes in k-Group,链表节点交换，用栈。
    
###[2015-11-1]
	First Missing Positive,找出第一个未出现的正整数，常数空间复杂度
	
###[2015-11-2]
	Longest Consecutive Sequence, 数组，unordered_map
	Maximum Depth of Binary Tree,递归
	Symmetric Tree,递归
	Reverse Words in a String,字符串翻转
	reorder list,链表操作
	
###[2015-11-7]
	LRU Cache, 实现LRU算法，unorderd_map + list,
	
###[2015-11-8]
	Maximum Product Subarray,最大连续乘积，动态规划
	Find Minimum in Rotated Sorted Array,找最小，二分法
	Find Minimum in Rotated Sorted Array 2,可重复数组，找最小数，二分法
	
###[2015-11-10]
	Min Stack,实现栈，能够常数时间输出最小值
	Intersection of Two Linked Lists,两个链表找交点
	Find Peak Element,找点
	Compare Version Numbers,比较两个字符串
	
###[2015-11-11]
	Maximum gap,桶排序，基数排序
	
###[2015-11-14]
	Excel Sheet Column Title,26进制处理
	Majority Element,求半数的元素，Moore voting algorithm。
	Majority_Element2,求1/3的元素，Moore voting algorithm.
	
###[2015-11-16]
	Excel Sheet Column Number,字符串
	Factorial Trailing Zeroes ,求n得阶乘后缀为0的个数
	Rotate Array,字符串翻转
	
###[2015-11-19]
	Binary Search Tree Iterator,BST,栈
	largestNumber,自定义排序，字典
	Repeated DNA Sequences,字符串，位运算，unordered_map
	
###[2015-11-20]
	Reverse Bits,位运算，bitset
	Number of 1 Bits,位运算
	
###[2015-11-21]
	House Robber,动态规划
	House Robber 2,动态规划
	Binary Tree Right Side View,树的层次遍历
	Number of Islands,并查集，DFS
	
###[2015-11-22]
	Bitwise AND of Numbers Range,位运算
	Happy Number
	Remove Linked List Elements,链表删除节点
	Delete Node in a Linked List,链表删除节点
	
###[2015-11-29]
	Count Primes,计算素数的个数
	Isomorphic Strings，单词替换，hash映射
###[20151214]
    Reverse Linked List,逆转链表，栈，或者递归或者遍历
    Course Schedule, dfs,bfs,拓扑排序
    Minimum Size Subarray Sum,数组
    Add and Search Word,字典树
    Word Search II, dfs+字典树
    Course Schedule II, 拓扑排序
    Different Ways to Add Parentheses,递归
###[20160109]
	Contains Duplicate, hash or sort 
	Shortest Palindrome,kmp匹配
	Ugly Number,递归
	Fraction to Recurring Decimal, hashmap.字符串
	Dungeon Game, 动态规划
	Best Time to Buy and Sell Stock IV，动态规划，需要使用局部最优和全局最优两种状态
	Kth Largest Element in an Array，分治、堆排序
###[20160123]
	Contains Duplicate II, unordered_map
	Contains Duplicate III,sort or multimap
	Rectangle Area,求两个矩形的全部覆盖面积
	Implement Stack using Queues,用两个队列来实现栈
	Invert Binary Tree,反转二叉树
	Maximal Square,求最大方形面积，动态规划问题
###[20160223]
    Basic Calculator,表达式计算，栈
    Basic Calculator II,表达式计算，用栈
    Wiggle Sort II,部分排序，荷兰国旗问题
	Summary Ranges,数组问题
	Power of Two,判断是否是2的指数，数学问题
	Power of Three，判断是否是2的幂，数学问题
    Count Complete Tree Nodes，计算完全树的节点个数，递归
    Expression Add Operators,表达式计算，DFS
###[20160301]
    Kth Smallest Element in a BST,递归，即中序遍历的思想；或者用栈
    Implement Queue using Stacks,用两个栈实现队列
    Number of Digit One,计算1的个数，数学题，找规律
    Palindrome Linked List，回文链表，用栈，或者将链表前半段逆转，然后前后依次比较
    Lowest Common Ancestor of a Binary Search Tree,查找两树节点的公共祖先，递归方法
	Add Digital,数学题，digital root问题
###[20160310]
    Lowest Common Ancestor of a Binary Tree,二叉树中的LCA问题，递归解决
    Product of Array Except Self,数组问题，求乘积
    Sliding Window Maximum,求滑动窗口的最大值，deque
    Binary Tree Paths,求所有从根节点到叶子节点的路径，DFS问题
    Ugly Number II,求第n个丑数，动态规划问题
    Single Number III,求数组中出现奇数次的数，位运算
    Missing Number,求无序数组中未出现的最小整数
    Integer to English Words,整数转字符串，字符串处理
	First Bad Version,二分法
	H-Index,求影响因子，排序或者hashtable
    H-Index II,求影响因子，要求O(logN)时间复杂度，二分法
    Perfect Squares,动态规划，最小硬币问题
###to be continued....