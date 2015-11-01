class Solution {
public:
	/*偷懒，stl*/
    bool search(vector<int>& nums, int target) {
            auto res = find(nums.begin(), nums.end(), target);
			if (res == nums.end())
				return false;
			else
				return true;
    }
};