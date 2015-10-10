class Solution {
public:
	/*
	Surrounded Regions BFS��ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(n)
	��Ҫ˼�룺�������ܵ�ÿ���ַ�������ǡ�O������ӵ�ǰ�ַ���ʼBFS�����������Χ��'O'���������С�
	������ɺ󣬽��ж���ɨ�裬����Ա����Ϊ'O',���ʾ����Χ��Ӧ��Ϊ'X'����������Ϊ'+',���ʾδ����Χ����Ϊ'O';
	*/
	void solve(vector<vector<char>>& board)
	{
		if (board.empty())
			return;
		const int m = board.size();
		const int n = board[0].size();
		//�����ܱ߽翪ʼ����
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
		//����ɨ��
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
		/*�жϵ�ǰ�ַ��Ƿ���'O'*/
		auto is_valid = [&](const state_t &s)
		{
			const int x = s.first;
			const int y = s.second;
			if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != 'O')
				return false;
			return true;
		};
		//�������������ص�ǰ�ַ�s������'O'����
		auto state_extend = [&](const state_t &s)
		{
			vector<state_t> result;
			const int x = s.first;
			const int y = s.second;
			//��������
			const state_t new_states[4] = { { x - 1, y }, { x + 1, y }, { x, y - 1 }, { x, y + 1 } };
			for (size_t i = 0; i < 4; i++)
			{
				if (is_valid(new_states[i]))
				{
					//���б������ȥ�صĹ���
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