//https://leetcode.com/problems/increasing-triplet-subsequence/
//直接DP时间复杂度和空间复杂度很高
bool increasingTriplet(vector<int>& nums)
{
    //状态转移方程为：dp[i]=max{dp[j]+1(0<=j<i,arr[j]<arr[i])}
    vector<int> ret(nums.size(), 1);
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (nums[j] < nums[i])
            {
                ret[i] = max(ret[i], ret[j] + 1);
                if (ret[i] == 3)
                    return true;
            }
        }
    }
    return false;
}
//时间复杂度O(N)，空间复杂度O(1)
bool increasingTriplet_v2(vector<int>& nums)
{
    int c1 = INT_MAX, c2 = INT_MAX;
for (int x : nums)
    {
        if (x <= c1)
        {
            c1 = x;           // c1 is min seen so far (it's a candidate for 1st element)
        }
        else if (x <= c2)
        {
            // here when x > c1, i.e. x might be either c2 or c3
            c2 = x;           // x is better than the current c2, store it
        }
        else
        {
            // here when we have/had c1 < c2 already and x > c2
            return true;      // the increasing subsequence of 3 elements exists
        }
    }
    return false;
}