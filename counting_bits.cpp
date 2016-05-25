//https://leetcode.com/problems/counting-bits/
vector<int> countBits(int num)
{
    vector<int> ret;
    for (size_t i = 0; i <= num; i++)
    {
        int count_one = valueCountOne(i);
        ret.push_back(count_one);
    }
    return ret;
}
//explanation,https://leetcode.com/discuss/92796/four-lines-c-time-o-n-space-o-n
//the i&(i-1) drop the lowest set bit 1
vector<int> countBits_v2(int num)
{
    vector<int> ret(num + 1, 0);
    for (size_t i = 1; i <= num; i++)
    {
        ret[i] = ret[i&(i - 1)] + 1;
    }
    return ret;
}