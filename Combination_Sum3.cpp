class Solution {
public:
    /*Combinations sum3*/
	vector<vector<int>> combinationSum3(int k, int n)
	{
		vector<int> path;
		vector<vector<int>> result;
		if (k == 0 || n == 0) return result;
		combinationSum3_dfs(result, path, 1, 0, k, 0, n);
		return result;
	}
	void combinationSum3_dfs(vector<vector<int>> &result, vector<int> path, int start,int count,int n_size,int sum, int target)
	{
		if (count == n_size&& sum == target)
		{
			sort(path.begin(), path.end());
			result.push_back(path);
			return;
		}
		if (sum >= target || count >= n_size)
			return;
		for (size_t i = start; i < 10; i++)
		{
			sum += i;
			path.push_back(i);
			combinationSum3_dfs(result, path, i + 1, count + 1, n_size, sum, target);
			sum -= i;
			path.pop_back();
		}
	}
};