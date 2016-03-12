//Single Number III,https://leetcode.com/problems/single-number-iii/
//位运算,先全部数异或运算，得到a^b；然后找a^b某位为1，其他为0的数，再遍历一遍数组，结束时的数就是a或b中的一个。
//最后，将得到的数再与a^b异或就是另一个数；
vector<int> singleNumber(vector<int>& nums)
{
    vector<int> ret(2);
    int res1 = 0, res2 = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        res1 ^= nums[i];
    }
    //temp只保留a^b中最右的1，其他置0
    int temp = res1&(~res1 + 1);
    for (int i = 0; i < nums.size(); i++)
    {
        if ((nums[i] & temp) != 0)
            res2 ^= nums[i];
    }
    ret[0] = res2;
    ret[1] = res2^res1;
    return ret;
}