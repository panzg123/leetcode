class Solution {
public:
	/*Pow(x,n)
	二分法， $x^n = x^{n/2} * x^{n/2} * x^{n\%2}
	时间复杂度 O(logn)，空间复杂度 O(1)
	直接遍历，超时*/
    double myPow(double x, int n)
	{
		if (n < 0) 
			return 1.0 / power_help(x, -n);
		else
			return power_help(x, n);

	}
	double power_help(double x, int n)
	{
		if (n == 0) return 1;
		double v = power_help(x, n / 2);
		if (n % 2 == 0)
			return v*v;
		else
			return v*v*x;
	}
};