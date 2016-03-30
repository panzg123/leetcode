class LIS
{
public:
    LIS(vector<int> _nums) :nums(_nums) {}
    //获得最长递增子序列
    vector<int> get_lis()
    {
        vector<int> len_dp = get_length();
        vector<int> ret = solve_lis(len_dp);
        return ret;
    }
private:
    vector<int> nums;
    //dp求解长度
    vector<int> get_length()
    {
        vector<int> ret(nums.size(), 1);
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                    ret[i] = max(ret[i], ret[j] + 1);
            }
        }
        return ret;
    }
    //从右向左获取最长递增子序列
    vector<int> solve_lis(vector<int> len_dp)
    {
        int len = 0;
        int index = 0;
        for (int i = 0; i < len_dp.size(); i++)
        {
            if (len_dp[i] > len)
            {
                len = len_dp[i];
                index = i;
            }
        }
        vector<int> ret(len, 0);
        ret[--len] = nums[index];
        for (int i = index; i >= 0; i--)
        {
            if (nums[i] < nums[index] && len_dp[i] == len_dp[index] - 1)
            {
                ret[--len] = nums[i];
                index = i;
            }
        }
        return ret;
    }
};