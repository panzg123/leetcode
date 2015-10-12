class Solution {
public:
	/*如果之前 SubArray 的总体和大于 0 的话，
	我们认为其对后续结果是有贡献的。这种情况下我们选择加入之前的 SubArray
	如果之前 SubArray 的总体和为 0 或者小于 0 的话，
	我们认为其对后续结果是没有贡献，甚至是有害的（小于 0 时）。这种情况下我们选择以这个数字开始，另起一个 SubArray。
	简单DP问题，f[j] = max {f[j − 1] + S[j], S[j]}
	*/
    int maxSubArray(vector<int>& nums) {
         int result = INT_MIN, f = 0;
        for (int i = 0; i < nums.size(); ++i)
            {
                f = max(f + nums[i], nums[i]);
                result = max(result, f);
            }
        return result;
    }
};