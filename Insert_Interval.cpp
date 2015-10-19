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
	/*Insert Interval 时间复杂度O(N) 不通过 */
    vector<Interval> insert(vector<Interval>& intervals, Interval new_interval) {
        // calculate the beginning of the affected range
		auto iter_s = lower_bound(intervals.begin(), intervals.end(), new_interval,
			[](const Interval & first, const Interval & second){
			return first.start < second.start;
		});
		if (iter_s != intervals.begin() && prev(iter_s)->end >= new_interval.start)
			new_interval.start = (--iter_s)->start;

		// calculate the end (pass-end by 1 actually) of the affected range
		auto iter_e = lower_bound(intervals.begin(), intervals.end(), new_interval,
			[](const Interval & first, const Interval & second){
			return first.end < second.end;
		});
		if (iter_e != intervals.end() && iter_e->start <= new_interval.end)
			new_interval.end = (iter_e++)->end;

		//copy unaffected range to results
		vector<Interval> results;
		copy(intervals.begin(), iter_s, back_inserter(results));
		results.push_back(new_interval);
		copy(iter_e, intervals.end(), back_inserter(results));
		return results;
    }
	/*通过*/
	vector<Interval> insert_interval2(vector<Interval>& intervals, Interval new_interval) 
	{
		// calculate the beginning of the affected range
		auto iter_s = lower_bound(intervals.begin(), intervals.end(), new_interval,
			[](const Interval & first, const Interval & second){
			return first.start < second.start;
		});
		if (iter_s != intervals.begin() && prev(iter_s)->end >= new_interval.start)
			new_interval.start = (--iter_s)->start;

		// calculate the end (pass-end by 1 actually) of the affected range
		auto iter_e = lower_bound(intervals.begin(), intervals.end(), new_interval,
			[](const Interval & first, const Interval & second){
			return first.end < second.end;
		});
		if (iter_e != intervals.end() && iter_e->start <= new_interval.end)
			new_interval.end = (iter_e++)->end;

		//copy unaffected range to results
		vector<Interval> results;
		copy(intervals.begin(), iter_s, back_inserter(results));
		results.push_back(new_interval);
		copy(iter_e, intervals.end(), back_inserter(results));
		return results;
	}
};