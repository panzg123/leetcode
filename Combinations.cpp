class Solution {
public:
	/*
	Combinations 
	递归，时间复杂度 O(n!)，空间复杂度 O(n)
	*/
	vector<vector<int>> combine(int n, int k)
	{
		vector<vector<int>> result;
		if (n < k) return result;
		vector<int> path;
		combine_help(result, n, 1, 0, path,k);
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
	void combine_help(vector<vector<int>> &result,int n,int k,int length,vector<int> &path,int target)
	{
		if (k<=n+1 && length == target)
		{
			result.push_back(path);
			return;
		}
		if (k>n) return;
		//选
		path.push_back(k);
		combine_help(result, n, k + 1, length + 1, path, target);
		path.pop_back();
		//不选
		combine_help(result, n, k + 1, length, path, target);
	}
};