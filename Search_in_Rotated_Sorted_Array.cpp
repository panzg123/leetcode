class Solution {
public:
	//ʱ�临�Ӷ� O(logn)���ռ临�Ӷ� O(1)
    int search(vector<int>& nums, int target) {
        int left = 0, mid = 0, right = nums.size() - 1;

    	while (left <= right)                    //������ߵ��±겻�����ұߣ�ѭ������
    	{
    		mid = (left + right) / 2;
    		if (nums[mid] == target)             //�м�����==target,�±��ҵ�������mid
    			return mid;
    
    		if (nums[left] <= nums[mid])         //˵��mid��ߵ�����û�з�ת
    		{
    			if (target >= nums[left] && target < nums[mid]) //���target���ڣ����Ȼ��nums[left,...mid-1]֮��
    				right = mid - 1;
    			else                                            //���target���ڣ����Ȼ��nums[mid+1,right]֮��
    				left = mid + 1;
    		}
    		else                                //˵��mid�ұߵ�����û�з�ת
    		{
    			if (target <= nums[right] && target > nums[mid]) //���target���ڣ����Ȼ��nums[lmid+1,right]֮��
    				left = mid + 1;
    			else                                             //���target���ڣ����Ȼ��nums[left,...mid-1]֮��
    				right = mid - 1;
    		}
    	}
    	return -1;                             //�����ڷ���-1         
    }
};