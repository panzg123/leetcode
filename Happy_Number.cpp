class Solution {
public:
    bool isHappy(int n) {
            unordered_set<int> set;
			while (n!=1)
			{
				int res = 0;
				while (n)
				{
					int a = n % 10;
					res += a*a;
					n /= 10;
				}
				n = res;
				auto find_res = set.find(n);
				if (find_res != set.end())
					return false;
				else
					set.insert(n);
			}
			return true;
    }
};