class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
		int step = 0; // 最小步数
		int left = 0;
		int right = 0; // [left, right] 是当前能覆盖的区间
		if (n == 1) return 0;
		while (left <= right) 
		{ // 尝试从每一层跳最远
			++step;
			const int old_right = right;
			for (int i = left; i <= old_right; ++i)
			{
				int new_right = i + nums[i];
				if (new_right >= n - 1) return step;
				if (new_right > right) right = new_right;
			}
			left = old_right + 1;
		}
		return 0;
    }
};