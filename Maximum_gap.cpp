//解法1，基数排序,先排序，在找数，参考https://leetcode.com/discuss/60533/share-my-12ms-c-solution-linear-time-space
const int RADIX = 256;
int COUNT[RADIX];

const int SHIFT[4] = {
(int)(log(pow(RADIX, 0))/log(2)),
(int)(log(pow(RADIX, 1))/log(2)),
(int)(log(pow(RADIX, 2))/log(2)),
(int)(log(pow(RADIX, 3))/log(2))
};

int GetPart(int num, int p)
{
    return (num >> SHIFT[p]) & (RADIX - 1);
}
int GetTimes(vector<int>& nums)
{
    int max = 0;

    for (auto m : nums)
    {
        max = max < m ? m : max;
    }
    return log(max) / log(RADIX);
}
int maximumGap(vector<int>& nums) 
{
    if (nums.size() <= 2)
    {
        if (nums.size() == 2)
        {
            return (
                nums[0] > nums[1] ?
                nums[0] - nums[1] :
                nums[1] - nums[0]);
        }
        return 0;
    }

    vector<int> temp(nums.size());
    int times = GetTimes(nums);

    for (int time = 0; time <= times; ++time)
    {
        for (int i = 0; i < RADIX; ++i)
        {
        COUNT[i] = 0;
        }
        for (auto m : nums)
        {
            ++COUNT[GetPart(m, time)];
        }
        for (int i = 1; i < RADIX; ++i)
        {
            COUNT[i] += COUNT[i - 1];
        }
        for (auto beg = nums.rbegin(); beg != nums.rend(); ++beg)
        {
            int j = GetPart(*beg, time);
            temp[COUNT[j] - 1] = *beg;
            --COUNT[j];
        }
        nums = temp;
    }

    int maximum = 0;

    for (auto beg = nums.begin() + 1; beg != nums.end(); ++beg)
    {
        int n = *beg - *(beg - 1);
        maximum =  n > maximum? n : maximum;   
    }
    return maximum;
}
//方法2，桶排序，参考https://leetcode.com/discuss/27754/my-c-code-12-ms-bucket-sort-o-n-time-and-space
	int maximumGap_v2(vector<int> &nums)
		{
			int n = nums.size();
			if (n < 2) return 0;
			int maxE = *max_element(nums.begin(), nums.end());
			int minE = *min_element(nums.begin(), nums.end());

			int len = maxE - minE;
			if (len <= 1) return len;
			vector<int> buck_max(n, INT_MIN);
			vector<int> buck_min(n, INT_MAX);

			for (int i = 0; i < n; i++) 
			{
				// note the divide and multiply order and the double cast
				// it's used to avoid the overflow and underflow during calculation
				int index = (double)(nums[i] - minE) / len * (n - 1);
				buck_max[index] = max(buck_max[index], nums[i]);
				buck_min[index] = min(buck_min[index], nums[i]);
			}

			int gap = 0, pre = buck_max[0];
			for (int i = 1; i < n; i++) 
			{
				if (buck_max[i] == INT_MIN) continue;
				gap = max(gap, buck_min[i] - pre);
				pre = buck_max[i];
			}
			return gap;
		}