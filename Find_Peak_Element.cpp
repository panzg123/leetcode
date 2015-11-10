class Solution {
public:
    int findPeakElement(vector<int>& nums) {
             int length = nums.size();
			if (length == 1 || nums[0] > nums[1])
				return 0;
			int i = 0;
			for (i = 1; i < length - 1;i++)
			{
				if (nums[i] > nums[i + 1] && nums[i] > nums[i - 1])
					return i;
			}
			if (nums[i - 1] < nums[i])
				return i;
    }
};