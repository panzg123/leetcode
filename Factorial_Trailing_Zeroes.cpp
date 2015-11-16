class Solution {
public:
	/*
	Factorial Trailing Zeroes 
	n!后缀0的个数 = n!质因子中5的个数 = floor(n/5) + floor(n/25) + floor(n/125) + ....
	*/
    int trailingZeroes(int n) {
        	int res = 0;
			while (n)
			{
				res += n / 5;
				n /= 5;
			}
			return res;
    }
};