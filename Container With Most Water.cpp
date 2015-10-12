/*Container With Most Water 贪心 双指针*/
	int maxArea(vector<int> &height)
	{
		int start = 0;
		int end = height.size() - 1;
		int result = INT_MIN;
		while (start < end) 
		{
			int area = min(height[end], height[start]) * (end - start);
			result = max(result, area);
			if (height[start] <= height[end]) 
				start++;
			else 
				end--;
		}
		return result;
	}