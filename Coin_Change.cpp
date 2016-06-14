		//https://leetcode.com/problems/coin-change/
		//换钱的最小货币数目,动态规划，时间复杂度和空间复杂度均为O(N*amount)
		//此处，空间复杂度可以优化为O（amount）
		int coinChange(vector<int>& coins, int amount) 
		{
			sort(coins.begin(), coins.end());
			vector<vector<int>> dp(coins.size(), vector<int>(amount+1,INT_MAX));
			for (int i = 0; i <= amount; i++)
			{
				if (i % coins[0])
					dp[0][i] = INT_MAX;
				else
					dp[0][i] = i / coins[0];
			}
			for (int i = 1; i < coins.size(); i++)
				dp[i][0] = 0;
			for (int i = 1; i < coins.size(); i++)
			{
				for (int j = 1; j <= amount; j++)
				{
					int left = INT_MAX;
					if (j - coins[i] >= 0 && dp[i][j - coins[i]]!=INT_MAX)
						left = dp[i][j - coins[i]] + 1;
					dp[i][j] = min(left, dp[i - 1][j]);
				}
			}
			return dp[coins.size() - 1][amount] == INT_MAX ? -1 : dp[coins.size() - 1][amount];
		}
		//时间复杂度O(N*amount),空间复杂度O(amount)
		int coinChange_v2(vector<int>& coins, int amount)
		{
			sort(coins.begin(), coins.end());
			vector<int> dp(amount+1, 0);
			for (int i = 1; i <= amount;i++)
			{
				if (i%coins[0])
					dp[i] = INT_MAX;
				else
					dp[i] = i / coins[0];
			}
			for (int i = 1; i < coins.size();i++)
			{
				for (int j = 1; j <= amount;j++)
				{
					int left = INT_MAX;
					if (j - coins[i] >= 0 && dp[j - coins[i]] != INT_MAX)
						left = dp[j - coins[i]] + 1;
					dp[j] = min(dp[j], left);
				}
			}
			return dp[amount] == INT_MAX ? -1 : dp[amount];
		}