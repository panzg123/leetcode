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
//时间复杂度为O(N)，具体参考：《面试指南》P386
int missingNumber_v2(vector<int>& nums)
{
    int l = 0;
    int r = nums.size();
    while (l<r)
    {
        if (nums[l] == l)
            l++;
        else if (nums[l] <= l-1 || nums[l]>r-1 || nums[nums[l]] == nums[l])
            nums[l] = nums[--r];
        else
            swap(nums[l], nums[nums[l]]);
    }
    return l;
}