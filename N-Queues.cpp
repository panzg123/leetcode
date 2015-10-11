class Solution 
{
public:
	/*N-Queens��N�ʺ����⣬DFS ���� + ��֦ 
	ʱ�临�Ӷ� O(n!)���ռ临�Ӷ� O(n)*/
	vector<vector<string>> solveNQueens(int n)
	{
		vector<vector<string>> result;
		vector<int> path;
		sloveNQueues_help(result, path, 0, n);
		return result;
	}
	void sloveNQueues_help(vector<vector<string>> &result,vector<int> &path,int start,int n)
	{
		if (start == n)
		{
			if (solve_isValid(path))
				result.push_back(get_queue(path));
			return;
		}
		if (!solve_isValid(path))
			return;
		for (size_t i = 0; i < n; i++)
		{
			//��ѯ�Ƿ���ڸ�ѡ��
			auto res = find(path.begin(), path.end(), i);
			if (res != path.end()) continue;
			path.push_back(i);
			sloveNQueues_help(result, path, start + 1, n);
			path.pop_back();
		}
	}
	/*����ѡ��·����ȡ�ʺ����з���*/
	vector<string> get_queue(vector<int> path)
	{
		int n = path.size();
		vector<string> res;
		for (size_t i = 0; i < n; i++)
		{
			string temp(n, '.');
			temp[path[i]] = 'Q';
			res.push_back(temp);
		}
		return res;
	}
	/*�жϵ�ǰ��ѡ������Ƿ���Ч*/
	bool solve_isValid(vector<int> path)
	{
		if (path.size() == 0) return true;
		for (size_t i = 0; i < path.size()-1; i++)
		{
			for (size_t j = i+1; j < path.size(); j++)
			{
				/*����������б����*/
				if (path[j]==path[i] || path[j] == (path[i] + (j - i)) || path[j]== (path[i] - (j - i)))
					return false;
			}
		}
		return true;
	}
}