		/*Majority Element II，，遍历*/
		vector<int> majorityElement2(vector<int>& nums)
		{
			vector<int> result;
			if (nums.size() == 0) return result;
			sort(nums.begin(), nums.end());
			int count = 0, curVal = nums[0];
			for (int i = 0; i < nums.size(); i++)
			{
				if (nums[i] == curVal) count++;
				else
				{
					curVal = nums[i];
					count = 1;
				}
				if (count > nums.size() / 3 && (result.size() == 0 || result[result.size() - 1] != curVal))
					result.push_back(curVal);
			}
			return result;
		}
		/*投票算法*/
		vector<int> majorityElement2_v2(vector<int>& nums) {
			vector<int> v;
			int size = nums.size();
			int n1 = 0, n2 = 0, cn1 = 0, cn2 = 0;
			for (int i = 0; i < size; i++)
			{
				if (nums[i] == n1)
				{
					cn1++;
				}
				else if (nums[i] == n2)
				{
					cn2++;
				}
				else if (cn1 == 0)
				{
					n1 = nums[i];
					cn1 = 1;
				}
				else if (cn2 == 0)
				{
					n2 = nums[i];
					cn2 = 1;
				}
				else
				{
					cn1--;
					cn2--;
				}
			}
			if (cn2 == 0 && size > 0)//用来解决[0 0]的情况
				n2 = nums[0] - 1;
			cn1 = 0;
			cn2 = 0;
			for (int i = 0; i<size; i++)
			{
				if (nums[i] == n1)
					cn1++;
				if (nums[i] == n2)
					cn2++;
			}
			if (cn1>size / 3)
				v.push_back(n1);
			if (cn2 > size / 3)
				v.push_back(n2);
			return v;
		}