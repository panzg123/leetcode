class Solution {
public:
	/*
	�������취�����ѣ�ʱ�临�Ӷ� O(2^n)���ռ临�Ӷ� O(n)
	ÿ��Ԫ�ض�������ѡ�񣺼�����߲�����
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
		//��ѡ��
		subsets_help(result, path, step + 1, nums);
		path.push_back(nums[step]);
		subsets_help(result, path, step + 1, nums);
		path.pop_back();
	}
};