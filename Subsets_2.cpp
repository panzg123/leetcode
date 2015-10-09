class Solution {
public:
	/*Subsets II 
	��subsets�Ĵ��롣
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
};