class Solution
{
public:
    /*
	Search Insert Position
	使用lower_bound，beat 0.01% cpp....
	*/
	int searchInsert(vector<int>& nums, int target)
	{
		return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
	}
	/*
	12ms, binary search, beats 0.47% of cpp submissions
	*/
	int searchInsert_v2(vector<int>& nums, int target)
	{
		auto first = nums.begin();
		auto last = nums.end();
		while (first != last)
		{
			auto mid = next(first, distance(first, last) / 2);
			if (target > *mid) first = ++mid;
			else last = mid;
		}
		return first-nums.begin();
	}
	
	//时间复杂度 O(logn)，空间复杂度 O(1)
	int searchInsert(vector<int>& nums, int target)
	{
		int searchInsert(vector<int>& nums, int target) {
		int left = 0, mid = 0, right = nums.size() - 1;

		if (nums.empty())
			return 0;

		while (left < right)                  //使用二分查找法
		{
			mid = (left + right) / 2;
			if (nums[mid] == target)         //如果nums[mid]==target,则nums中存在target，则返回mid
				return mid;
			if (nums[mid] > target)          //nums[mid] > target,如果存在target，则必然在nums[left,mid-1]
				right = mid - 1;
			else                             //nums[mid] < target,如果存在target，则必然在nums[left,mid-1]
				left = mid + 1;
		}

		if (nums[left] >= target)            //nums[left]>=target,taget出现的位置和插入的相同
			return left;
		else                                 //nums[left]<target,则在left+1处插入
			return left + 1;
	}
};