class Solution {
public:
		/*Find Minimum in Rotated Sorted Array*/
		int findMin(vector<int>& nums)
		{
			//也可以一行代码搞定，直接 return *(min_element(nums.begin(),nums.end()));
			int begin=0, end=nums.size()-1;
			if (end == 0) return nums[0];
			if (nums[end] > nums[0]) return nums[0];
			while (begin < end)
			{
				if (begin == end - 1) 
					return min(nums[begin], nums[end]);
				int mid = (begin + end)/ 2;
				if (nums[mid] < nums[begin])
					end = mid;
				else
					begin = mid;
			}
		}
};