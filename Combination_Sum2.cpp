class Solution
{
public:
    void combinationSumHelper(vector<vector<int>>& result, vector<int>& candidates,
                              int right, int target, vector<int>& partResult)
    {
        int upperBound = upper_bound(candidates.begin(), candidates.begin() + right, target) - candidates.begin() - 1;
        if (upperBound < 0) return;

        for (int i = upperBound; i >= 0; i--)
            {
                int newTarget = target - candidates.at(i);
                partResult.push_back(candidates.at(i));
                if (newTarget == 0)
                    {
                        result.push_back(partResult);
                        partResult.pop_back();

                        // skip duplicate number to prevent duplicate solution
                        while (i > 0 && candidates.at(i) == candidates.at(i - 1))
                            i--;
                        continue;
                    }

                // i+1 is changed to i to only use a number once
                combinationSumHelper(result, candidates, i, newTarget, partResult);
                partResult.pop_back();

                // skip duplicate number to prevent duplicate solution
                while (i > 0 && candidates.at(i) == candidates.at(i - 1))
                    i--;
            }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
    {
        vector<vector<int>> result;
        if (candidates.empty()) return result;

        sort(candidates.begin(), candidates.end());

        vector<int> partResult;
        combinationSumHelper(result, candidates, candidates.size(), target, partResult);
		for (auto& r : result)
            reverse(r.begin(), r.end());
        return result;
    }
};