class Solution {
public:
	/*动态规划，当前位置可以有i-1上一步，i-2上两步，*
	f[n]=f[n-1]+f[n-2]*/
    int climbStairs(int n) {
        int pre1 = 1, pre2 = 1;
		int cur = 0;
		if (n==0)
		{
			return pre1;
		}
		if (n==1)
		{
			return pre2;
		}
		for (size_t i = 2; i <= n; i++)
		{
			cur = pre1 + pre2;
			pre1 = pre2;
			pre2 = cur;
		}
		return cur;
    }
};