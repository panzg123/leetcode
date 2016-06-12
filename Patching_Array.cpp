		//https://leetcode.com/problems/patching-array/?sort=votes
		//reference,https://leetcode.com/discuss/102653/c-8ms-greedy-solution-with-explanation
		int minPatches(vector<int>& nums, int n) 
		{
			int cnt = 0, i = 0;
			long long maxNum = 0;
			while (maxNum < n)
			{
				if (i < nums.size() && nums[i] <= maxNum + 1)
					maxNum += nums[i++];
				else
				{
					maxNum += maxNum + 1; cnt++;
				}
			}
			return cnt;
		}