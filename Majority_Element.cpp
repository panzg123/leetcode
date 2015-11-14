		/*Majority Element O(N)时间，O(N)空间*/
		int majorityElement(vector<int>& nums)
		{
			unordered_map<int, int> count;
			int length = nums.size();
			for (int i = 0; i < length;i++)
			{
				auto res = count.find(nums[i]);
				if (res == count.end())
					count[nums[i]] = 1;
				else
					count[nums[i]]++;
				if (count[nums[i]] > length / 2)
					return nums[i];
			}
		}
		/*Moore's voting algorithm 常数空间复杂度*/
		int majorityElement_v2(vector<int>& nums)
		{
			int curValue=0, curCount = 0;
			for (int i = 0; i < nums.size();i++)
			{
				if (curCount == 0)
				{
					curCount = 1;
					curValue = nums[i];
				}
				else if (curValue == nums[i])
					curCount++;
				else
					curCount--;
			}
			return curValue;
		}