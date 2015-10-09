#include<vector>
#include<algorithm>
#include <iostream>
#include <string>
#include<sstream>
#include <unordered_map>
#include <numeric>
#include <map>
#include<stack>
#include<queue>
#include<random>
#include<regex>
#include<functional>



typedef struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x) :val(x), next(nullptr){}
}ListNode;

typedef struct TreeLinkNode{
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
}TreeLinkNode;

typedef int Record;
typedef std::vector<Record> File;

struct Input
{
	Record value;
	size_t index;
	const File* file;

	explicit Input(const File* f)
		: value(-1),
		index(0),
		file(f)
	{ }

	bool next()
	{
		if (index < file->size())
		{
			value = (*file)[index];
			++index;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator<(const Input& rhs) const
	{
		// make_heap to build min-heap, for merging
		return value > rhs.value;
	}
};

//leetcode�϶������Ľڵ㶨������
typedef struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr){}
}TreeNode;