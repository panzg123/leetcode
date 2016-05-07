//
// Created by panzg on 2016/5/7.
//

typedef pair<int,int> myPair;

class comparePair {
public:
    bool operator() (const myPair& lhs, const myPair& rhs) const
    {
        return lhs.second < rhs.second;
    }
};
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> counter;
        vector<int> res ;
        for (auto it: nums) {
            counter[it]++;
        }

        priority_queue<myPair,vector<myPair>, comparePair> heap;

        for (auto it = counter.begin(); it != counter.end(); it++) {
            heap.push(make_pair(it->first,it->second));
        }

        for (int i = 0; i < k; i++) {
            res.push_back((heap.top()).first);
            heap.pop();
        }
        return res;
    }
};