//Move Zeroes,https://leetcode.com/problems/move-zeroes/
//用begin_idx记录非零位置，剩余的位置填充0
void moveZeroes(vector<int>& nums)
{
    int begin_idx = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != 0)
            nums[begin_idx++] = nums[i];
    }
    while (begin_idx < nums.size())
    {
        nums[begin_idx++] = 0;
    }
}