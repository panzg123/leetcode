class Solution {
public:
    int mySqrt(int x) {
        int left = 1, right = x / 2;
		int last_mid; //记录最近一次mid
		if (x < 2) return x;
		while (left <= right)
		{
			const int mid = left + (right - left) / 2;
			// 不要用 x > mid * mid，会溢出
			if (x / mid > mid)
			{
				left = mid + 1;
				last_mid = mid;
			}
			else if (x / mid < mid)
				right = mid - 1;
			else
				return mid;
		}
		return last_mid;
    }
	/*Integer Newton ，快很多
	参考解法：https://en.wikipedia.org/wiki/Integer_square_root#Using_only_integer_division
	*/
	int mySqrt_v2(int x)
	{
		long long r = x;
		while (r*r > x)
			r = (r + x / r) / 2;
		return r;
	}
};