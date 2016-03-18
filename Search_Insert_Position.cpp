class Solution
{
public:
    /*
	Search Insert Position
	ʹ��lower_bound��beat 0.01% cpp....
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
	
	//ʱ�临�Ӷ� O(logn)���ռ临�Ӷ� O(1)
	int searchInsert(vector<int>& nums, int target)
	{
		int searchInsert(vector<int>& nums, int target) {
		int left = 0, mid = 0, right = nums.size() - 1;

		if (nums.empty())
			return 0;

		while (left < right)                  //ʹ�ö��ֲ��ҷ�
		{
			mid = (left + right) / 2;
			if (nums[mid] == target)         //���nums[mid]==target,��nums�д���target���򷵻�mid
				return mid;
			if (nums[mid] > target)          //nums[mid] > target,�������target�����Ȼ��nums[left,mid-1]
				right = mid - 1;
			else                             //nums[mid] < target,�������target�����Ȼ��nums[left,mid-1]
				left = mid + 1;
		}

		if (nums[left] >= target)            //nums[left]>=target,taget���ֵ�λ�úͲ������ͬ
			return left;
		else                                 //nums[left]<target,����left+1������
			return left + 1;
	}
};