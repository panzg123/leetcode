//https://leetcode.com/problems/integer-break/ , DP
int integerBreak(int n)
{
    vector<int> dp(n+1,1);
    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j < i; j++)
        {
            dp[i] = max(dp[i], max(dp[j], j)*max(dp[i - j], i - j));
        }
    }
    return dp[n];
}