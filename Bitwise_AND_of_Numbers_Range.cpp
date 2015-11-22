class Solution
{
public:
    /*
    	Bitwise AND of Numbers Range，位运算
    	当m!=n，那么最末位必定等0，因为[m,n]必定包含奇偶数，相与最末位等0。当m=n的时候，后面都是0，前面的就是这个范围内的数按位相与的相同部分。
    	举例来说：m=4(0000 0100), n=6(0000 0110), 那么范围[4,6]中包含4、5、6，即0000 0100, 0000 0101, 0000 0110，所有的结果按位与得到0000 0100。
    	初始：m!=n，于是m,n分别右移一位得到0000 0010, 0000 0011，同时偏移量offset+1；
    	m!=n，于是m,n继续右移一位得到0000 0001, 0000 0001，同时偏移量offset+1；
    	m=n，得到结果m<<offset。
    	*/
    int rangeBitwiseAnd(int m, int n)
    {
        int res = 0;
        int offset = 0;
        while (m != n)
        {
            m >>= 1;
            n >>= 1;
            offset++;
        }
        return m << offset;
    }
};