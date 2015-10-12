class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int cur_pro = 0;
		int length = prices.size();
		if (length < 2) return 0;
		int cur_min= prices[0];
		for (size_t i = 1; i < length; i++)
		{
			cur_pro = max(cur_pro, prices[i] - cur_min);
			cur_min = min(cur_min, prices[i]);
		}
		return cur_pro;
    }
};