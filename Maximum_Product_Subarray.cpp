		/*Maximum Product Subarray 直接两层循环，超时*/
		int maxProduct(vector<int>& nums)
		{
			int length = nums.size();
			int result = INT_MIN;
			for (int i = 0; i < length;i++)
			{
				int temp = 1;
				for (int j = i; j < length;j++)
				{
					temp *= nums[j];
					result = max(result, temp);
				}
			}
			return result;
		}
		/*
		动态规划，当前状态包含三种情况：
		1. current maxValue * A[i]  if A[i]>0
		2. current minValue * A[i]  if A[i]<0
		3. A[i]
		所以代码中需要记录当前最小值和当前最大值两个值
		*/
		int maxProduct_dp(vector<int>& nums)
		{
			int length = nums.size();
			if (length <= 0) return 0;
			if (length == 1) return nums[0];
			int curMax = nums[0];
			int curMin = nums[0];
			int result = nums[0];
			for (int i = 1; i < length;i++)
			{
				int temp_max = nums[i] * curMax;
				int temp_min = nums[i] * curMin;
				curMax = max(max(temp_max, temp_min), nums[i]);
				curMin = min(min(temp_max, temp_min), nums[i]);
				result = max(result, curMax);
			}
			return result;
		}