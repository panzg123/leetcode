class Solution {
public:
    /*判断当前的选择队列是否有效*/
	bool solve_isValid(vector<int> path)
	{
		if (path.size() == 0) return true;
		for (size_t i = 0; i < path.size()-1; i++)
		{
			for (size_t j = i+1; j < path.size(); j++)
			{
				/*竖向方向，两个斜向方向*/
				if (path[j]==path[i] || path[j] == (path[i] + (j - i)) || path[j]== (path[i] - (j - i)))
					return false;
			}
		}
		return true;
	}
	/*N-Queues 2*/
	int totalNQueens(int n)
	{
		int  result=0;
		vector<int> path;
		sloveNQueues_help(result, path, 0, n);
		return result;
	}
	void sloveNQueues_help(int &result, vector<int> &path, int start, int n)
	{
		if (start == n)
		{
			if (solve_isValid(path))
				result++;
			return;
		}
		if (!solve_isValid(path))
			return;
		for (size_t i = 0; i < n; i++)
		{
			//查询是否存在该选择
			auto res = find(path.begin(), path.end(), i);
			if (res != path.end()) continue;
			path.push_back(i);
			sloveNQueues_help(result, path, start + 1, n);
			path.pop_back();
		}
	}
};