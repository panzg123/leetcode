class Solution {
public: 
	//时间复杂度 O(logn)，空间复杂度 O(1)
    vector<int> searchRange(vector<int>& nums, int target) {
    	vector<int> result({ -1, -1 });
    	if (nums.empty())               //如果nums为空，之间返回
    		return result;
    
    	int left = 0, mid = 0, right = nums.size() - 1;
    	while (left <= right)           //确定最左边的下标
    	{
    		mid = (left + right) / 2;
    		if (nums[mid] >= target)
    			right = mid - 1;
    		else
    			left = mid + 1;
    	}
    
    	if (left > nums.size() - 1 || nums[left] != target)  //nums中不存在target
    		return result;
    
    	result[0] = left;                //保存最左边的下标
    
    	right = nums.size() - 1;
    	while (left <= right)            //确定最右边的下标
    	{
    		mid = (left + right) / 2;
    		if (nums[mid] <= target)
    			left = mid + 1;
    		else
    			right = mid - 1;
    	}
    	result[1] = right;              //保存最左边的下标
    
    	return result;
    }
};