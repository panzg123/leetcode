//Kth Largest Element in an Array ,直接用排序,12ms
int findKthLargest(vector<int>& nums, int k)
{
    sort(nums.begin(), nums.end());
    return nums[nums.size() - k];
}
//Kth Largest Element in an Array ,堆,28ms,其它方法请参考：https://leetcode.com/discuss/36966/solution-explained
int findKthLargest_v2(vector<int>& nums, int k)
{
    vector<int> temp_vec = nums;
    make_heap(temp_vec.begin(), temp_vec.end());
    while (k > 1)
    {
        std::pop_heap(temp_vec.begin(), temp_vec.end());
        temp_vec.pop_back();
        k--;
    }
    return temp_vec.front();
}
//待更新