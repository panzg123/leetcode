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
};