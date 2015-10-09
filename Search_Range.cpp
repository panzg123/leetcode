/*Search for a range*/
class searchRange_class
{
public:
    /*������ʱ�临�Ӷ�ΪO(n),�ռ临�Ӷ�O(1)*/
    vector<int> searchRange(vector<int>& nums, int target)
    {
        vector<int> result = { -1, -1 };
        int flag1 = 0, flag2 = 0;
        for (size_t i = 0; i < nums.size(); i++)
            {
                if (nums[i] == target)
                    {
                        if (flag1 == 0)
                            {
                                result[0] = i;
                                result[1] = i;
                                flag1 = 1;
                            }
                        else
                            result[1] = i;
                    }
            }
        return result;
    }
    /*ʹ��STL ʱ�临�Ӷ� O(logn)���ռ临�Ӷ� O(1)*/
    vector<int> searchRenge_STL(vector<int> &nums, int target)
    {
        vector<int> result = { -1, -1 };
        auto low = std::lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        auto up = std::upper_bound(nums.begin(), nums.end(), target) - nums.begin();
        if (nums[low] == target)
            {
                result[0] = low;
                result[1] = up - 1;
            }
        return result;
    }
    /*
    ����ʵ�� lower_bound �� upper_bound
    ʱ�临�Ӷ� O(logn)���ռ临�Ӷ� O(1)
    */
    vector<int> searchRange_imple(int A[], int n, int target)
    {
        auto lower = my_lower_bound(A, A + n, target);
        auto uppper = my_upper_bound(lower, A + n, target);
        if (lower == A + n || *lower != target)
            return vector<int> { -1, -1 };
        else
            return vector<int> {distance(A, lower), distance(A, prev(uppper))};
    }
    template<typename ForwardIterator, typename T>
    ForwardIterator my_lower_bound(ForwardIterator first,
                                   ForwardIterator last, T value)
    {
        while (first != last)
            {
                auto mid = next(first, distance(first, last) / 2);
                if (value > *mid) first = ++mid;
                else last = mid;
            }
        return first;
    }
    template<typename ForwardIterator, typename T>
    ForwardIterator my_upper_bound(ForwardIterator first,
                                   ForwardIterator last, T value)
    {
        while (first != last)
            {
                auto mid = next(first, distance(first, last) / 2);
                if (value >= *mid) first = ++mid; // �� lower_bound ���˲�ͬ
                else last = mid;
            }
        return first;
    }
};