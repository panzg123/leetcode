//Ugly Number II，https://leetcode.com/problems/ugly-number-ii/
//直接查找第n个丑数，超时
int nthUglyNumber(int n)
{
    int start = 1;
    int ugly_idx = 0;
    while (ugly_idx < n)
    {
        if (isUgly(start++))
            ugly_idx++;
    }
    return start-1;
}
//用DP算法求解,
int nthUglyNumber_dp(int n)
{
    if (n == 1)
        return 1;
    vector<int> ret(n);
    ret[0] = 1;
    //指向2,3,5的索引
    int p2_idx = 0, p3_idx = 0, p5_idx = 0;
    for (int i = 1; i < n; i++)
    {
        ret[i] = min(ret[p2_idx] * 2, min(ret[p3_idx] * 3, ret[p5_idx] * 5));
        //索引前移
        if (ret[i] == ret[p2_idx] * 2)
            p2_idx++;
        if (ret[i] == ret[p3_idx] * 3)
            p3_idx++;
        if (ret[i] == ret[p5_idx] * 5)
            p5_idx++;
    }
    return ret[n - 1];
}