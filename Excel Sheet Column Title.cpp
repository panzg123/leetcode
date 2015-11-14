class Solution {
public:
    string convertToTitle(int n) {
            string s;
			while (n)
			{
				int a = (n-1)% 26;
				s.insert(s.begin(), 'A'+a);
				n=(n-1)/26;
			}
			return s;
    }
};