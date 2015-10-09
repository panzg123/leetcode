class Solution
{
public:
    /*sort colors ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(1)*/
    void sortColors(vector<int> &nums)
    {
        int count[3] = {0};
        for (size_t i = 0; i < nums.size(); i++)
            {
                count[nums[i]]++;
            }

        int index = 0;
        for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < count[i]; j++)
                    {
                        nums[index++] = i;
                    }
            }
    }
};