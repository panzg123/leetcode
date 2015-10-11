/*Combination Sum dfs */
vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    vector<int> path;
    vector<vector<int>> result;
    combinationSum_dfs(result, path, 0, 0, candidates, target);
    return result;
}
void combinationSum_dfs(vector<vector<int>> &result,vector<int> path,int start,int sum,vector<int> candidates,int target)
{
    if (target == 0)
        return;
    if (sum == target)
        {
            sort(path.begin(), path.end());
            result.push_back(path);
            return;
        }
    if (sum > target)
        return;
    for (size_t i = start; i < candidates.size(); i++)
        {
            sum += candidates[i];
            path.push_back(candidates[i]);
            combinationSum_dfs(result, path, i, sum, candidates, target);
            sum -= candidates[i];
            path.pop_back();
        }
}