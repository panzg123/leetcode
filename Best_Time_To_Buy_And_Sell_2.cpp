	/*Best Time to Buy and Sell Stock2
	思路：将所有距离为1的有利润的部分相加即可*/
	int maxProfit2(vector<int>& prices)
	{
		int sum = 0;
		for (int i = 1; i < prices.size(); i++) 
		{
			int diff = prices[i] - prices[i - 1];
			if (diff > 0) sum += diff;
		}
		return sum;
	}