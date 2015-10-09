class Solution {
public:
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
		subsets_help(result, path, step + 1, nums);
		path.pop_back();
	}
};