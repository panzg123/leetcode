class Solution {
public:
	/*
	Surrounded Regions BFS，时间复杂度 O(n)，空间复杂度 O(n)
	主要思想：遍历四周的每个字符，如果是‘O’，则从当前字符开始BFS遍历，如果周围是'O'，则加入队列。
	遍历完成后，进行二次扫描，如果仍被标记为'O',则表示被包围，应改为'X'；如果被标记为'+',则表示未被包围，仍为'O';
	*/
	void solve(vector<vector<char>>& board)
	{
		if (board.empty())
			return;
		const int m = board.size();
		const int n = board[0].size();
		//从四周边界开始遍历
		for (size_t i = 0; i < n; i++)
		{
			bfs(board, 0, i);
			bfs(board, m - 1, i);
		}
		for (size_t i = 1; i < m-1; i++)
		{
			bfs(board, i, 0);
			bfs(board, i, n - 1);
		}
		//二次扫描
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				if (board[i][j] == 'O')
					board[i][j] = 'X';
				else if (board[i][j] == '+')
					board[i][j] = 'O';
			}
		}
	}
private:
	void bfs(vector<vector<char>> &board, int i, int j)
	{
		typedef pair<int, int> state_t;
		queue<state_t> q;
		const int m = board.size();
		const int n = board[0].size();
		/*判断当前字符是否是'O'*/
		auto is_valid = [&](const state_t &s)
		{
			const int x = s.first;
			const int y = s.second;
			if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != 'O')
				return false;
			return true;
		};
		//匿名函数，返回当前字符s的四周'O'集合
		auto state_extend = [&](const state_t &s)
		{
			vector<state_t> result;
			const int x = s.first;
			const int y = s.second;
			//上下左右
			const state_t new_states[4] = { { x - 1, y }, { x + 1, y }, { x, y - 1 }, { x, y + 1 } };
			for (size_t i = 0; i < 4; i++)
			{
				if (is_valid(new_states[i]))
				{
					//既有标记又有去重的功能
					board[new_states[i].first][new_states[i].second] = '+';
					result.push_back(new_states[i]);
				}
			}
			return result;
		};
		//BFS
		state_t start = { i, j };
		if (is_valid(start))
		{
			board[i][j] = '+';
			q.push(start);
		}
		while (!q.empty())
		{
			auto cur = q.front();
			q.pop();
			auto new_states = state_extend(cur);
			for (auto s : new_states)
				q.push(s);
		}
	}
};