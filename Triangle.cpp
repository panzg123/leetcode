class Solution {
public:
	/*简单dp*/
    int minimumTotal(vector<vector<int>>& triangle) {
       for (int i = triangle.size()-2; i >=0; i--)
		{
			for (size_t j = 0; j < i+1; j++)
			{
				triangle[i][j] = min(triangle[i + 1][j], triangle[i + 1][j + 1])+triangle[i][j];
			}
		}
		return triangle[0][0];
    }
};