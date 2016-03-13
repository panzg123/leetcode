// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int lower = 1, upper = n, mid;
        while(lower < upper) {
			//用lower + (upper - lower) / 2，而不是(lower + upper) / 2
            mid = lower + (upper - lower) / 2;
            if(!isBadVersion(mid)) lower = mid + 1;
            else upper = mid;
        }
        return lower;
    }
};