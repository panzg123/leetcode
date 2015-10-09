class Solution
{
public:
	/*
	Search a 2D Matrix 2
	900ms,beats 10% of cpp submissions
	*/
	bool searchMatrix(vector<vector<int>>& matrix, int target)
	{
		int n = matrix[0].size();
		for (size_t i = 0; i < matrix.size(); i++)
		{
			//剪枝
			if (matrix[i][0] > target || matrix[i][n - 1] < target)
				continue;
			//二分查找
			if (std::binary_search(matrix[i].begin(), matrix[i].end(), target))
				return true;
		}
		return false;
	}
	/*
	Search a 2D Matrix 2，复杂度为O(M+N)
	272ms,beats 95%
	*/
	bool searchMatrix_v2(vector<vector<int>>& matrix, int target) {

		int row = 0;
		int col = matrix[0].size() - 1;

		while (row < matrix.size() && col >= 0) {
			if (matrix[row][col] == target) return true;
			if (matrix[row][col] < target) { row++; continue; }
			if (matrix[row][col] > target) { col--; continue; }
		}
		return false;

	}
};