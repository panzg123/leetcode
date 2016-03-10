//Product of Array Except Self,解法1，直接遍历，复杂度O(N*N)，超时
vector<int> productExceptSelf(vector<int>& nums)
{
    vector<int> result(nums.size());
    for (size_t i = 0; i < nums.size(); i++)
    {
        result[i] = accumulate(nums.begin(), next(nums.begin(),i), 1,multiplies<int>())*
                    accumulate(next(nums.begin(),i+1), nums.end(), 1, multiplies<int>());
    }
    return result;
}
//Product of Array Except Self,解法2，用两个数组来记录前后两端的乘积
vector<int> productExceptSelf_v2(vector<int>& nums)
{
    //记录前i个元素的乘积
    vector<int> from_begin_product(nums.size());
    //记录后i个元素的乘积
    vector<int> from_end_product(nums.size());
    from_begin_product[0] = 1;
    from_end_product[0] = 1;
    for (size_t i = 1; i < nums.size(); i++)
    {
        from_begin_product[i] = from_begin_product[i-1] * nums[i - 1];
        from_end_product[i] = from_end_product[i-1] * nums[nums.size() - i];
    }
    vector<int> result(nums.size());
    for (size_t i = 0; i < nums.size(); i++)
    {
        //result[i]等于前i个元素和后size-1-i个元素的乘积
        result[i] = from_begin_product[i] * from_end_product[nums.size()-1 - i];
    }
    return result;
}