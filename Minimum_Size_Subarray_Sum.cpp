class Solution
{
public:
    /*Minimum Size Subarray Sum*/
    int minSubArrayLen(int s, vector<int>& nums)
    {
        int length = nums.size();
        int min_length = length;
        int index1 = 0, index2 = 0;
        int sum = 0;
        while (sum < s && index2<length)
        {
            sum += nums[index2];
            index2++;
        }
        if (index2 == length && sum<s) return 0;
        index2--;
        min_length = index2+1; //初始化最小长度，数组头部
        while (index2 < length)
        {
            while (sum>=s) //压缩数组
                sum -= nums[index1++];
            min_length = min(min_length, index2 - index1+2);//更新最小长度
            index2++;
            if (index2<length) //index2++
                sum += nums[index2];
        }
        return min_length;
    }
};