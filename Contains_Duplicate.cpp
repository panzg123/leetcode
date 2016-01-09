//Contains Duplicate
bool containsDuplicate(vector<int>& nums)
{
    unordered_map<int, int> map_;
    for (int i = 0; i < nums.size(); i++)
    {
        auto it = map_.find(nums[i]);
        if (it != map_.end())
            return true;
        else
            map_[nums[i]] = 1;
    }
    return false;
}