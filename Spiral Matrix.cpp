class Solution {
public:
    /*Spiral Matrix*/
		vector<int> spiralOrder(vector<vector<int>>& matrix)
		{
			vector<int> result;
			if (matrix.empty())
				return result;
			int beginX = 0, endX = matrix[0].size() - 1;
			int beginY = 0, endY = matrix.size() - 1;
			while (true)
			{
				//上
				for (int j = beginX; j <= endX; ++j)
					result.push_back(matrix[beginY][j]);
				if (++beginY > endY)
					break;
				//右
				for (int i = beginY; i <= endY; ++i)
					result.push_back(matrix[i][endX]);
				if (beginX >--endX)
					break;
				//下
				for (int j = endX; j >= beginX; --j)
					result.push_back(matrix[endY][j]);
				if (--endY < beginY)
					break;
				//左
				for (int i = endY; i >= beginY; --i)
					result.push_back(matrix[i][beginX]);
				if (++beginX > endX) break;
			}
			return result;
		}
};