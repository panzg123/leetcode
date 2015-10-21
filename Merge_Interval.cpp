/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert_interval(vector<Interval>& intervals, Interval newInterval)
	{
		vector<Interval>::iterator it = intervals.begin();
		while (it != intervals.end()) 
		{
			if (newInterval.end < it->start) 
			{
				intervals.insert(it, newInterval);
				return intervals;
			}
			else if (newInterval.start > it->end)
			{
				it++;
				continue;
			}
			else 
			{
				newInterval.start = min(newInterval.start, it->start);
					newInterval.end = max(newInterval.end, it->end);
				it = intervals.erase(it);
			}
		}
		intervals.insert(intervals.end(), newInterval);
		return intervals;
	}
	/*merge intervals
	复用Insert Intervals
	时间复杂度 O(n1+n2+...)，空间复杂度 O(1)
	*/
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> result;
		for (int i = 0; i < intervals.size(); i++)
		{
			insert_interval(result, intervals[i]);
		}
		return result;
    }
};