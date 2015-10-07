class Solution
{
public:
    /*Unique Binary Search Trees
	动态规划，时间复杂度 O(n^2)，空间复杂度 O(n)
	f(i) =i∑k=1 f(k − 1) × f(i − k)*/
	int numTrees(int n)
	{
		int *f = new int[n+1];
		memset(f, 0, sizeof(int)*(n + 1));
		f[0] = 1;
		f[1] = 1;
		for (size_t i = 2; i <= n; i++)
		{
			for (size_t j = 1; j <= i; j++)
			{
				f[i] += f[i - j] * f[j - 1];
			}
		}
		return f[n];
		delete[] f;
	}
};