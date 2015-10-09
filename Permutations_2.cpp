class Solution {
public:
	/*
	Permutations 2
	用next_permutation , 时间复杂度 O(n!)，空间复杂度 O(1)
	*/
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		do
		{
			result.push_back(nums);
		} while (std::next_permutation(nums.begin(), nums.end()));
		return result;
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