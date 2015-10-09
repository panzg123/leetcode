class Solution
{
public:
	/*
	Search a 2D Matrix
	二分查找,12ms，时间复杂度 O(logn)，空间复杂度 O(1)
	*/
	bool searchMatrix(vector<vector<int>>& matrix, int target)
	{
		int rows = matrix.size();
		int colums = matrix[0].size();
		int length = rows*colums;
		int first = 0, last = length - 1;
		while (first <= last)
		{
			int mid = (first + last) / 2;
			if (matrix[mid / colums][mid%colums] == target)
				return true;
			else if (matrix[mid / colums][mid%colums] < target)
				first = mid + 1;
			else
				last = mid - 1;
		}
		return false;
	}
};