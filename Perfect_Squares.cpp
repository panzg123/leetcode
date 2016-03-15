//最小硬币问题，动态规划
int minCoins(vector<int>& coins, int sum)
{
    if (coins.size() == 0 || sum < 0)
        return -1;
    int length = coins.size();
    int max = INT_MAX;
    vector <vector<int>> dp(length, vector<int>(sum+1,0));
    for (int i = 1; i <= sum; i++)
    {
        dp[0][i] = INT_MAX;
        if (i - coins[0] >= 0 && dp[0][i - coins[0]] != INT_MAX)
            dp[0][i] = dp[0][i - coins[0]] + 1;
    }
    int left = 0;
    for (int i = 1; i < length; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            left = INT_MAX;
            if (j - coins[i] >= 0 && dp[i][j - coins[i] != INT_MAX])
                left = dp[i][j - coins[i]] + 1;
            dp[i][j] = min(left, dp[i - 1][j]);
        }
    }
    return dp[length - 1][sum] != INT_MAX ? dp[length - 1][sum] : -1;
}
//Perfect Squares,https://leetcode.com/problems/perfect-squares/
//memory limit exceede
int numSquares(int n)
{
    if (n < 0)
        return 0;
    vector<int> num;
    for (int i = 1; i*i <= n; i++)
    {
        num.push_back(i*i);
    }
    return minCoins(num, n);
}
//980ms,beat 1.7%
int numSquares_v2(int n)
{
    vector<int> nums;
    vector<int> dp(n + 1, INT_MAX);
    for (int i = 1; i*i <= n; i++)
    {
        nums.push_back(i*i);
        dp[i*i] = 1;
    }

    for (int i = 1; i < n; i++)
        for (int j = 0; j < nums.size(); j++)
        {
            if (dp[i] != INT_MAX&&i + nums[j] <= n)
                dp[i + nums[j]] = min(dp[i + nums[j]], dp[i] + 1);
        }
    return dp[n] == INT_MAX ? n : dp[n];
}
//134ms,beat 0.7%,普通方法太耗时，尝试static dp,bfs,math等方法
//更快的方法请参考：https://leetcode.com/discuss/58056/summary-of-different-solutions-bfs-static-and-mathematics
int numSquares_v3(int n)
{
    if (n < 0)
        return 0;
    vector<int> nums;
    vector<int> dp(n + 1, 0);
    for (int i = 1; i*i <= n; i++)
    {
        nums.push_back(i*i);
    }
    for (int j = 1; j <= n; j++)
    {
        if (j - nums[0] >= 0 && dp[j - nums[0]] != INT_MAX)
            dp[j] = dp[j - nums[0]] + 1;
    }
    int left = 0;
    for (int i = 1; i < nums.size(); i++)
    {
        for (int j = 1; j <= n; j++)
        {
            left = INT_MAX;
            if (j - nums[i] >= 0 && dp[j - nums[i]] != INT_MAX)
                left = dp[j - nums[i]] + 1;
            dp[j] = min(left, dp[j]);
        }
    }
    return dp[n] != INT_MAX ? dp[n] : -1;
}