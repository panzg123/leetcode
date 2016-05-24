class topKFrequent_Solutions_v2
{
    typedef pair<int,int> myPair;
    class cmp
    {
    public:
        bool operator()(const myPair& lhs, const myPair& rhs)
        {
            return lhs.second < rhs.second;
        }
    };
    class Solution
    {
    public:
        vector<int> topKFrequent(vector<int>& nums,int k)
        {
            unordered_map<int, int> counter;
            vector<int> ret;
            for each (auto var in nums)
            {
                counter[var]++;
            }
            priority_queue<myPair, vector<myPair>, cmp> heap;
            for each (auto var in counter)
            {
                heap.push(make_pair(var.first, var.second));
            }
            for (int i = 0; i < k; i++)
            {
                ret.push_back(heap.top().first);
                heap.pop();
            }
            return ret;
        }
    };
};