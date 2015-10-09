class Solution {
public:
	/*Subsets II 
	用subsets的代码。
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
};