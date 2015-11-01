/*First Missing Positive 时间复杂度和空间复杂度都是o(n)，不符合要求*/
		int firstMissingPositive(vector<int>& nums) 
		{
			unordered_map<int, bool> m_map;
			for (int i = 0; i < nums.size();i++)
			{
				m_map[nums[i]] = true;
			}
			int index = 1;
			for (int i = 0; i < nums.size();i++)
			{
				auto res = m_map.find(index);
				if (res == m_map.end())
				{
					return index;
				}
				else
					index++;
			}
			return index;
		}
		/*first missing positive 空间复杂度为常数
		思路：可以把数组中的元素放入“合适”的位置时，例如将1放在0位置上，2放在1位置上。。。，最后遍历数组，如果某个位置上的数不合适，则返回该位置上“合适”的数，
		*/
		int firstMissingPositive_v2(vector<int> &nums)
		{
			int size = nums.size();
			if(size == 0) return 1;
			for (int i = 1; i <= size;i++)
			{
				//将元素放入合适的位置
				while (nums[i-1] != i)
				{
					if (nums[i-1]<0 || nums[i-1]>size||nums[i-1] == nums[nums[i-1]-1])
					{
						break;
					}
					int temp = nums[i - 1];
					nums[i - 1] = nums[temp - 1];
					nums[temp - 1] = temp;
				}
			}
			for (int i = 1; i <= size;i++)
			{
				if (nums[i - 1] != i)
					return i;
			}
			return size + 1;
		}