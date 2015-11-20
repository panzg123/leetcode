class Solution {
public:
	/*Number of 1 Bits 位运算*/
    int hammingWeight(uint32_t n) {
            int count = 0;
			for (int i = 0; i < 32 && n>0; i++, n >>= 1)
			    if (n & 0x1)
			    	count++;
			return count;
    }
};