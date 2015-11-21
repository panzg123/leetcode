class Solution
{
public:
    /*House Robber II 动态规划*/
    int rob2(vector<int>& nums)
    {
        if (nums.empty())
        {
            return 0;
        }
        else if (nums.size() == 1)
        {
            return nums[0];
        }
        //不选最后一个节点
        vector<int> temp1(next(nums.begin()),nums.end());
        int value1 = rob2_helper(temp1);
        //不选第一个节点
        vector<int> temp2(nums.begin(), prev(nums.end()));
        int value2 = rob2_helper(temp2);
        return max(value1, value2);

    }
    //求nums的rob value
    int rob2_helper(vector<int> nums)
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