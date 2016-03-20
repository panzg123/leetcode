class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        reverse(matrix.begin(), matrix.end());                 //先将matrix从上到下反转

    	for (int i = 0; i < matrix.size(); ++i)                //按左对角线交换对称元素
    	{
    		for (int j = 0; j < i; ++j)
    		{
    			swap(matrix[i][j], matrix[j][i]);
    		}
    	}
    }
};