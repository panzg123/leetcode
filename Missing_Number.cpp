//Missing Number,https://leetcode.com/problems/missing-number/
//直接先排序，时间复杂度为O(N*N)
int missingNumber(vector<int>& nums)
{
    if (nums.size() == 0)
        return 0;
    //排序
    sort(nums.begin(), nums.end());
    int start = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != start)
            return start;
        start++;
    }
    return start;
}
//时间复杂度为O(N)，具体参考：《面试指南》P386，l表示目前出现的数的范围[0,l],r表示可能出现的最大数值
int missingNumber_v2(vector<int>& nums)
{
    int l = 0;
    int r = nums.size();
    while (l<r)
    {
        //正常出现
        if (nums[l] == l)
            l++;
        //重复出现[0,l]的某数;或直接超出最大值；或者重复出现[l,r]的某数,此时都应该缩小r
        else if (nums[l] <= l-1 || nums[l]>r-1 || nums[nums[l]] == nums[l])
            nums[l] = nums[--r];
        //出现[l+1,r]之间的数，只是顺序不正确，此时需要交换位置
        else
            swap(nums[l], nums[nums[l]]);
    }
    return l;
}