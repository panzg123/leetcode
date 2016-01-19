class Solution
{
public:
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
    /*
    Best Time to Buy and Sell Stock IV，动态规划，需要使用局部最优和全局最优两种状态
    参考：http://www.cnblogs.com/grandyang/p/4295761.html
    */
    int maxProfit(int k, vector<int>& prices)
    {
        if (prices.empty())
            return 0;
        if (k >= prices.size())
            return maxProfit2(prices);
        vector<int> g(k + 1, 0);
        vector<int> l(k + 1, 0);
        for (int i = 0; i < prices.size() - 1; ++i)
        {
            int diff = prices[i + 1] - prices[i];
            for (int j = k; j >= 1; --j)
            {
                l[j] = max(g[j - 1] + max(diff, 0), l[j] + diff);
                g[j] = max(g[j], l[j]);
            }
        }
        return g[k];
    }
};