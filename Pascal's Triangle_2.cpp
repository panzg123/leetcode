class Solution {
public:
	/*Pascal’s Triangle 2 
	滚动数组，时间复杂度 O(n^2)，空间复杂度 O(n)*/
    vector<int> getRow(int rowIndex) {
        vector<int> array;
		for (int i = 0; i <= rowIndex;i++)
		{
			for (int j = i - 1; j > 0;j--)
			{
				array[j] = array[j - 1] + array[j];
			}
			array.push_back(1);
		}
		return array;
    }
};