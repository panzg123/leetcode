class Solution {
public:
	/*Find Minimum in Rotated Sorted Array 2 二分法*/
    int findMin(vector<int>& nums) {
           int n = nums.size();
			if (n == 0) return 0;

			int l = 0, r = n - 1;
			while (l <= r)
			{
				if (l == r) return nums[r];
				int mid = (l + r) / 2;

				while (nums[mid] == nums[l] && l<mid) l++;
				while (nums[mid] == nums[r] && r>mid) r--;

				if (nums[mid] > nums[r])
					l = mid + 1;
				else
					r = mid;
			}
    }
};