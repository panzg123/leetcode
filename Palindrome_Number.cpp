class Solution {
public:
    /*Palindrome Number
	思路：不断地取第一位和最后一位（ 10 进制下）进行比较，相等则取第二位和倒数第二位，直到完成比较或者中途找到了不一致的位。*/
	bool isPalindrome(int x)
	{
		if (x < 0) return false;
		int d = 1; // 除数
		while (x / d >= 10) d *= 10;
		while (x > 0) 
		{
			int q = x / d; // 前
			int r = x % 10; // 后
			if (q != r) return false;
			x = x % d / 10; //先取余，再除，就去除了收尾两位
			d /= 100;
		}
		return true;
	}
};