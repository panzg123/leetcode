class Solution
{
public:
	/*merge sorted array
	时间复杂度 O(m+n)，空间复杂度 O(1)*/
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		int ia = m - 1, ib = n - 1, icur = m + n - 1;
		while (ia >= 0 && ib >= 0)
		{
			nums1[icur--] = (nums1[ia] > nums2[ib]) ? nums1[ia--] : nums2[ib--];
		}
		while (ib >= 0)
			nums1[icur--] = nums2[ib--];
	}
};