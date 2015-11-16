class Solution {
public:
		/*Rotate Array 分成前后两端分别旋转*/
		void rotate(vector<int>& nums, int k)
		{
			int length = nums.size();
			if (k == length) //直接返回
			{
				return;
			}
			else if (k > length) //取余
				k %= length;
			rotate_helper(nums, 0, length-k-1);
			rotate_helper(nums, length-k, length - 1);
			rotate_helper(nums, 0, length - 1);
		}
		void rotate_helper(vector<int> &nums,int start,int end)
		{
			while (start<end)
			{
				int temp = nums[start];
				nums[start] = nums[end];
				nums[end] = temp;
				start++;
				end--;
			}
		}
};