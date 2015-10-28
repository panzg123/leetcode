class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
		{
			int k = nums1.size() + nums2.size();
			//偶数
			if (k % 2 == 0)
				return (
				findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2) +
				findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2 + 1)
				) / 2;
			//奇数
			else
				return findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2 + 1);
		}
		double findKthSortedArrays(vector<int>::const_iterator nums1, int m, vector<int>::const_iterator nums2, int n, int k) 
		{
			if (m > n)
				return findKthSortedArrays(nums2, n, nums1, m, k);
			//边界条件
			if (m == 0)
				return *(nums2 + k - 1);
			//返回第1小的值，即min(num[0],num1[0])
			if (k == 1)
				return min(*nums1, *nums2);

			//下面是判断B[k-1]和A[k-1]关系；
			int mk = min(m, k / 2);
			int nk = k - mk;
			//如果A[k/2-1]=B[k/2-1]，返回其中一个；
			if (*(nums1 + mk - 1) == *(nums2 + nk - 1))
				return *(nums1 + mk - 1);
			//当A[k/2-1] < B[k/2-1],删除A[0，k/2-1]
			else if (*(nums1 + mk - 1) < *(nums2 + nk - 1))
				return findKthSortedArrays(nums1 + mk, m - mk, nums2, n, k - mk);
			//当A[k/2-1] > B[k/2-1],删除B[0，k/2-1]
			else
				return findKthSortedArrays(nums1, m, nums2 + nk, n - nk, k - nk);
		}
};