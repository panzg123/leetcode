class Solution
{
public:
    /*Reverse Bits 位运算*/
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t res = 0;
        for (int i = 0; i < 32; i++, n >>= 1)
            res = (res << 1) | (n & 1);
        return res;
    }
    /*Reverse Bits 使用bitset对整数和二进制进行转换*/
    typedef unsigned  int uint32_t;
    uint32_t reverseBits(uint32_t n)
    {
        string s = bitset<32>(n).to_string();
        reverse(s.begin(), s.end());
        return bitset<32>(s).to_ulong();
    }
};