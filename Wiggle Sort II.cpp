//直接先排序，后拷贝,时间复杂度O(N*logN)，空间复杂度O(N)
void wiggleSort(vector<int>& nums)
{
    int length = nums.size();
    sort(nums.begin(), nums.end());
    copy(nums.cbegin(), nums.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
    vector<int> result(nums);
    int j = length - 1;
    for (int i = 1; i < length; i += 2, j--)
    {
        result[i] = nums[j];
    }
    for (int i = 0; i < length; i += 2, j--)
    {
        result[i] = nums[j];
    }
    nums = result;
}
//时间复杂度O(N)，空间复杂度O(1)，使用nth_element算法和three_way partition方法
//参考 https://leetcode.com/discuss/77133/o-n-o-1-after-median-virtual-indexing
//荷兰国旗问题请参考：http://www.cnblogs.com/gnuhpc/archive/2012/12/21/2828166.html
void wiggleSort_v2(vector<int>& nums)
{
    int n = nums.size();

    // Find a median.
    auto midptr = nums.begin() + n / 2;
    nth_element(nums.begin(), midptr, nums.end());
    int mid = *midptr;

    // Index-rewiring.
    #define A(i) nums[(1+2*(i)) % (n|1)]

    // 3-way-partition-to-wiggly in O(n) time with O(1) space.
    int i = 0, j = 0, k = n - 1;
    while (j <= k)
    {
        if (A(j) > mid)
            swap(A(i++), A(j++));
        else if (A(j) < mid)
            swap(A(j), A(k--));
        else
            j++;
    }
}