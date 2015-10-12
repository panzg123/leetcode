class Solution {
public:
  bool canJump(vector<int>& nums)
	{
		int reach = 1; // 最右能跳到哪里
		int n = nums.size();
		//更新reach
		for (int i = 0; i < reach && reach < n; ++i)
			reach = max(reach, i + 1 + nums[i]);
		return reach >= n;
	}
	/*dp*/
	bool canJump_dp(vector<int> &nums) {
		int n = nums.size();
		if (n == 0) return true;
		// 逆向下楼梯，最左能下降到第几层
		int left_most = n - 1;
		for (int i = n - 2; i >= 0; --i)
		if (i + nums[i] >= left_most)
			left_most = i;
		return left_most == 0;
	}
};