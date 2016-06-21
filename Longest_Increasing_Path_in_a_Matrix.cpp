		//https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
		//暴力DFS，超时,可以对长度进行存储，见longestIncreasingPath_dp
		int longestIncreasingPath(vector<vector<int>>& matrix) 
		{
			int ret = 0;
			for (int i = 0; i < matrix.size();i++)
			{
				for (int j = 0; j < matrix.size();j++)
				{
					ret = max(ret, longestIncreasingPath_helper(matrix, 1, i, j));
				}
			}
			return ret;
		}
		int longestIncreasingPath_helper(vector<vector<int>>& matrix,int cur_length,int cur_x,int cur_y)
		{
			int ret = cur_length;
			if (cur_x > 0 && matrix[cur_x - 1][cur_y] > matrix[cur_x][cur_y])
				ret = max(ret, longestIncreasingPath_helper(matrix, cur_length + 1, cur_x - 1, cur_y));
			if (cur_y < matrix[0].size()-1 && matrix[cur_x][cur_y+1] > matrix[cur_x][cur_y])
				ret = max(ret, longestIncreasingPath_helper(matrix, cur_length + 1, cur_x, cur_y + 1));
			if (cur_x < matrix.size()-1 && matrix[cur_x + 1][cur_y] > matrix[cur_x][cur_y])
				ret = max(ret, longestIncreasingPath_helper(matrix, cur_length + 1, cur_x + 1, cur_y));
			if (cur_y > 0 && matrix[cur_x][cur_y - 1] > matrix[cur_x][cur_y])
				ret = max(ret, longestIncreasingPath_helper(matrix, cur_length + 1, cur_x, cur_y - 1));
			return ret;
		}
		//dfs+dp,400ms
		int longestIncreasingPath_dp(vector<vector<int>>& matrix)
		{
			int rows = matrix.size();
			if (!rows) return 0;
			int cols = matrix[0].size();

			//dp[x][y]表示以(x,y)为起点的最大长度
			vector<vector<int>> dp(rows, vector<int>(cols, 0));
			std::function<int(int, int)> dfs = [&](int x, int y) 
			{
				if (dp[x][y]) 
					return dp[x][y];
				vector<vector<int>> dirs = { { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };
				for (auto &dir : dirs) //遍历四个方向，找到最大值
				{
					int xx = x + dir[0], yy = y + dir[1];
					if (xx < 0 || xx >= rows || yy < 0 || yy >= cols) 
						continue;
					if (matrix[xx][yy] <= matrix[x][y]) 
						continue;
					dp[x][y] = std::max(dp[x][y], dfs(xx, yy));
				}
				//+1
				return ++dp[x][y];
			};

			int ret = 0;
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					ret = std::max(ret, dfs(i, j));
				}
			}
			return ret;
		}
		//同样DFS+DP，但只需60ms，优化在function函数对象
		class longestIncreasingPathSolution {
			vector<vector<int>> visited;
			int height = 0, width = 0;
			int floodfill(vector<vector<int>>& matrix, int cur, int i, int j)
			{
				if (i < 0 || i >= height || j < 0 || j >= width)
					return 0;
				if (matrix[i][j] <= cur)
					return 0;
				if (visited[i][j] > 0)
					return visited[i][j];
				int r = floodfill(matrix, matrix[i][j], i + 1, j);
				int l = floodfill(matrix, matrix[i][j], i - 1, j);
				int u = floodfill(matrix, matrix[i][j], i, j + 1);
				int d = floodfill(matrix, matrix[i][j], i, j - 1);
				visited[i][j] = max(r, max(l, max(u, d))) + 1;
				return visited[i][j];
			}
		public:
			int longestIncreasingPath(vector<vector<int>>& matrix) {
				if (matrix.empty())
					return 0;
				height = matrix.size(), width = matrix[0].size();
				visited.resize(height, vector<int>(width));
				int max_len = 0;
				for (int i = 0; i < height; ++i)
					for (int j = 0; j < width; ++j)
						max_len = max(max_len, floodfill(matrix, INT_MIN, i, j));
				return max_len;
			}
		};