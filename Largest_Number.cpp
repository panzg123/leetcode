class Solution
{
public:
    string largestNumber(vector<int>& nums)
    {
        /*定义匿名函数，进行排序*/
        sort(nums.begin(), nums.end(),
             [](const int& l_num, const int& r_num)
        {
            return to_string(l_num) + to_string(r_num) > to_string(r_num) + to_string(l_num);
        });
        if (nums[0] == 0) return "0";
        //累加
        return std::accumulate(nums.begin(), nums.end(), string(""), [](const string& a, int b)
        {
            return a + to_string(b);
        });
    }
};