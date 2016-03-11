//Sliding Window Maximum,https://leetcode.com/problems/sliding-window-maximum/
//直接判断，时间复杂度为O(N*N)
vector<int> maxSlidingWindow(vector<int>& nums, int k)
{
    if (nums.size() == 0)
        return vector<int>();
    vector<int> result(nums.size() - k + 1);
    for (size_t i = 0; i < nums.size() - k + 1; i++)
    {
        result[i] = *max_element(next(nums.begin(), i), next(nums.begin(), i + k));
    }
    return result;
}
//deque很适用本场景,时间复杂度为O(N)
vector<int> maxSlidingWindow_v2(vector<int>& nums, int k)
{
    vector<int> ret;
    deque<int> max;
    for (int i = 0; i < nums.size(); ++i)
    {
        //当当前值更大，则更新最大值
        while (!max.empty() && nums[i] > max.back())
        {
            max.pop_back();
        }
        max.push_back(nums[i]);
        //从第k个元素开始压入返回值
        if (i >= k - 1)
        {
            ret.push_back(max.front());
            //如果当前窗口的最大值是该窗口的第一个值，则需要弹出
            if (nums[i - k + 1] == max.front())
            {
                max.pop_front();
            }
        }
    }
    return ret;
}