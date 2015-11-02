class Solution {
public:
    /*Longest Consecutive Sequence,用unordered_set，O(n)*/
		int longestConsecutive(vector<int>& nums) 
		{
			int len = 0, candidate, val;
			unordered_set<int> set(nums.begin(), nums.end());
			while (!set.empty()) 
			{
				val = *set.begin();
				set.erase(val);
				candidate = 1;
				//处理比val大的数
				for (int i = val + 1; set.find(i) != set.end(); ++i) 
				{
					set.erase(i);
					candidate++;
				}
				//处理比val小的数
				for (int i = val - 1; set.find(i) != set.end(); --i)
				{
					set.erase(i);
					candidate++;
				}
				len = max(len, candidate);
			}
			return len;
		}
		/*Longest Consecutive Sequence 偷懒不符合O(n)要求*/
		int longestConsecutive_v1(vector<int>& nums)
		{
			sort(nums.begin(), nums.end());
			int count = 1;
			int result = 1;
			for (size_t i = 1; i < nums.size();i++)
			{
				if (nums[i] == nums[i - 1]+1)
					count++;
				else if (nums[i] == nums[i-1])
				{
					continue;
				}
				else
				{
					result = max(result, count);
					count = 1;
				}
			}
			return max(result, count);
		}
};