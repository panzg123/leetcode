class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        reverse(matrix.begin(), matrix.end());                 //�Ƚ�matrix���ϵ��·�ת

    	for (int i = 0; i < matrix.size(); ++i)                //����Խ��߽����Գ�Ԫ��
    	{
    		for (int j = 0; j < i; ++j)
    		{
    			swap(matrix[i][j], matrix[j][i]);
    		}
    	}
    }
};