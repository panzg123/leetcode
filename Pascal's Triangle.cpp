class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result;
		if (numRows == 0) return result;
		result.push_back(vector<int>(1,1));
		for (int i = 1; i < numRows;i++)
		{
			vector<int> temp = {1};
			for (int j = 1; j < i;j++)
			{
				temp.push_back(result[i - 1][j - 1] + result[i - 1][j]);
			}
			temp.push_back(1);
			result.push_back(temp);
		}
		return result;
    }
};