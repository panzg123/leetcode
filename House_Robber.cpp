class Solution
{
public:
    /*House Robber ，简单动态规划*/
    int rob(vector<int>& nums)
    {
        if (nums.empty())
        {
            return 0;
        }
        else if (nums.size() == 1)
        {
            return nums[0];
        }

        vector<int> dp(nums.size(), 0);
        dp[nums.size() - 1] = nums[nums.size() - 1];
        dp[nums.size() - 2] = max(nums[nums.size() - 2], nums[nums.size() - 1]);

        for (int i = (int)nums.size() - 3; i >= 0; --i)
        {
            dp[i] = max(nums[i] + dp[i + 2],
                        dp[i + 1]);
        }

        return dp[0];
    }
};