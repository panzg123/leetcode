//Find the Duplicate Number,https://leetcode.com/problems/find-the-duplicate-number/
//抽屉原理，整个数组中如果小于等于n/2的数的数量大于n/2，说明1到n/2这个区间是肯定有重复数字的
//否则，在[n/2+1,n]的范围中存在重复数
int findDuplicate(vector<int> nums)
{
    int min = 0, max = nums.size() - 1;
    while (min <= max)
    {
        // 找到中间那个数
        int mid = min + (max - min) / 2;
        int cnt = 0;
        // 计算总数组中有多少个数小于等于中间数
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] <= mid)
            {
                cnt++;
            }
        }
        // 如果小于等于中间数的数量大于中间数，说明前半部分必有重复
        if (cnt > mid)
        {
            max = mid - 1;
            // 否则后半部分必有重复
        }
        else
        {
            min = mid + 1;
        }
    }
    return min;
}
//映射找环法,快慢指针的方法
//https://leetcode.com/discuss/61514/understood-solution-space-without-modifying-explanation
int findDuplicate_v2(vector<int> nums)
{
    int slow = 0;
    int fast = 0;
    do
    {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }
    while (slow != fast);
    int find = 0;
    while (find != slow)
    {
        slow = nums[slow];
        find = nums[find];
    }
    return find;
}