
	/*
	纯模拟：
	基本字符:I V X L C D M
	相应的阿拉伯数字表示为 1 5 10 50 100 500 1000
	另外:
	1.相同的数字连写，所表示的数等于这些数字相加得到的数，如：Ⅲ = 3；
	2.小的数字在大的数字的右边，所表示的数等于这些数字相加得到的数， 如：Ⅷ = 8；Ⅻ = 12；
	3.小的数字，（限于Ⅰ、X 和C）在大的数字的左边，所表示的数等于大数减小数得到的数，如：Ⅳ= 4；Ⅸ= 9；
	4.正常使用时，连写的数字重复不得超过三次。（表盘上的四点钟“IIII”例外）
	5.在一个数的上面画一条横线，表示这个数扩大1000倍。
	*/
class Solution {
public:
   string intToRoman(int num)
	{
		const int radix[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
		const string symbol[] = { "M", "CM", "D", "CD", "C", "XC",
			"L", "XL", "X", "IX", "V", "IV", "I" };
		string roman;
		for (size_t i = 0; num > 0; i++)
		{
			int count = num / radix[i];
			num = num % radix[i];
			for (; count > 0; --count)
				roman += symbol[i];
		}
		return roman;
	}
};