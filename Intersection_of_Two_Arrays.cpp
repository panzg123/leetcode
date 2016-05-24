//Intersection of Two Arrays,unordered_set
vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
{
    unordered_set<int> m(nums1.begin(), nums1.end());
    vector<int> res;
for (auto a : nums2)
        if (m.count(a))
        {
            res.push_back(a);
            m.erase(a);
        }
    return res;
}
//先排序，然后遍历
vector<int> intersection_v2(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> ret;
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    size_t i = 0, j = 0;
    while (i< nums1.size() && j < nums2.size())
    {
        if (nums1[i] == nums2[j])
        {
            if (ret.empty() || nums1[i] != ret.back())
                ret.push_back(nums1[i]);
            j++;
            i++;
        }
        else if (nums1[i] > nums2[j])
        {
            j++;
        }
        else
            i++;
    }
    return ret;
}
//用压缩集合的思想
vector<int> intersection_v3(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> ret;
    //TODO,http://blog.csdn.net/jie1991liu/article/details/13168255
    return ret;
}