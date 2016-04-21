//https://leetcode.com/problems/longest-increasing-subsequence/
//简单动态规划，复杂度O(N^2)
class Solution
{
public:
    int lengthOfLIS(vector<int>& nums)
    {
        if (nums.size() == 1 || nums.size() == 0)
            return nums.size();
        vector<int> dp(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};