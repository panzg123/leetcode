//H-Index II,https://leetcode.com/problems/h-index-ii/
//需要时间复杂度为O(logN),二分法
int hIndex2(vector<int>& citations)
{
    int low_idx = 0;
    int up_idx = citations.size() - 1;
    while (low_idx<up_idx)
    {
        int mid = low_idx + (up_idx - low_idx) / 2;
        if (citations[mid] < (citations.size() - mid))
            low_idx = mid + 1;
        else
            up_idx = mid;
    }
    //citations[low_idx]用来处理全为0的特殊情况
    return min(citations[low_idx],static_cast<int>(citations.size())-low_idx);
}