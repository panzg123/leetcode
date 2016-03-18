class Solution {
public:
	//时间复杂度 O(logn)，空间复杂度 O(1)
    int search(vector<int>& nums, int target) {
        int left = 0, mid = 0, right = nums.size() - 1;

    	while (left <= right)                    //数组左边的下标不大于右边，循环继续
    	{
    		mid = (left + right) / 2;
    		if (nums[mid] == target)             //中间数字==target,下标找到，返回mid
    			return mid;
    
    		if (nums[left] <= nums[mid])         //说明mid左边的数字没有反转
    		{
    			if (target >= nums[left] && target < nums[mid]) //如果target存在，则必然在nums[left,...mid-1]之间
    				right = mid - 1;
    			else                                            //如果target存在，则必然在nums[mid+1,right]之间
    				left = mid + 1;
    		}
    		else                                //说明mid右边的数字没有反转
    		{
    			if (target <= nums[right] && target > nums[mid]) //如果target存在，则必然在nums[lmid+1,right]之间
    				left = mid + 1;
    			else                                             //如果target存在，则必然在nums[left,...mid-1]之间
    				right = mid - 1;
    		}
    	}
    	return -1;                             //不存在返回-1         
    }
};