//Contains Duplicate III，直接使用sort排序
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
{
    if (nums.size() < 2) return false;
    vector<pair<long, int>> v;
    for (int i = 0; i < nums.size(); i++)
    {
        v.push_back(pair<long, int>((long)nums[i], i));
    }
    //排序
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < nums.size(); i++)
    {
        int j = i + 1;
        while (j < v.size())
        {
            if (v[j].first - v[i].first > t)  break;
            else if (abs(v[i].second - v[j].second) <= k)
            {
                return true;
            }
            else
                j++;
        }
    }
    return false;
}

static bool cmp(pair<long, int> a, pair<long, int> b)
{
    return a.first < b.first;
}
//Contains Duplicate III,使用multimap排序，和上面的思想一样
//reference:https://leetcode.com/discuss/60011/c-28ms-solution-using-multimap
bool containsNearbyAlmostDuplicate_multimap(vector<int>& nums, int k, int t)
{
    multimap<long, int> map;
    //插入multimap中排序
    for (int i = 0; i < nums.size(); i++)
    {
        map.insert(make_pair(nums[i], i));
    }
    auto p1 = map.begin();
    while (p1 != map.end())
    {
        auto p2 = p1;
        p2++;
        while (p2 != map.end() && p2->first - p1->first <= t)
        {
            if (abs(p1->second - p2->second) <= k)
                return true;
            p2++;
        }
        p1++;
    }
    return false;
}