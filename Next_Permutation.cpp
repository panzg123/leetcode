class Solution
{
public:
    /*找到最后两位满足：nums[i] < nums[j]，然后交换*/
    void nextPermutation(vector<int>& nums)
    {
        int n = nums.size();
        for (int i = n - 1; i >= 0; i--)
            {
                for (int j = n - 1; j > i; j--)
                    {
                        if (nums[i] < nums[j])
                            {
                                swap(nums[i], nums[j]);
                                sort(nums.begin() + i + 1, nums.end());
                                return;
                            }
                    }
            }
        sort(nums.begin(), nums.end());
    }
	/*假如不能使用stl，可以自己实现next_permutation*/
    template<typename BidiIt>
    bool next_permutation(BidiIt first, BidiIt last)
    {
		// Get a reversed range to simplify reversed traversal.
        const auto rfirst = reverse_iterator<BidiIt>(last);
        const auto rlast = reverse_iterator<BidiIt>(first);
		// Begin from the second last element to the first element.
        auto pivot = next(rfirst);
		// Find `pivot`, which is the first element that is no less than its
		// successor. `Prev` is used since `pivort` is a `reversed_iterator`.
        while (pivot != rlast && *pivot >= *prev(pivot))
            ++pivot;
		// No such elemenet found, current sequence is already the largest
		// permutation, then rearrange to the first permutation and return false.
        if (pivot == rlast)
            {
                reverse(rfirst, rlast);
                return false;
            }
		// Scan from right to left, find the first element that is greater than
		// `pivot`.
        auto change = find_if(rfirst, pivot, bind1st(less<int>(), *pivot));
        swap(*change, *pivot);
        reverse(rfirst, pivot);
        return true;
    }
	
	//时间复杂度 O(n)，空间复杂度 O(m)
	void nextPermutation(vector<int>& nums) {
		int sz = nums.size();
		if (sz <= 1)                                      //nums的长度<=1，直接返回
		{
			return;
		}

		int pivot = sz - 1;
		while (pivot>0 && nums[pivot] <= nums[pivot - 1]) //寻找最后两位满足:nums[pivot] > nums[pivot-1]
		{
			--pivot;
		}

		if (pivot == 0)                                   //数组元素的大小均为递减
		{
			sort(nums.begin(), nums.end());
			return;
		}

		int tmp = pivot-1;                               //记录第一个非递减组合的第一个数的下标
		int i = sz - 1;
		while (nums[tmp] >= nums[i])                     //寻找第一个大于nums[tmp]的数
		{
			--i;
		}
		swap(nums[tmp], nums[i]);
		sort(nums.begin() + pivot, nums.end());          //因为从nums.begin()+pivot之后的元素就能为递减，使用sort和reverse均可
	}
};