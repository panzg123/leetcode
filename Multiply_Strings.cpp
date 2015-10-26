class Solution {
public:
	/**
	*Multiply Strings
	*常见的做法是将字符转化为一个 int，一一对应，形成一个 int 数组
	*时间复杂度 O(n*m)，空间复杂度 O(n+m)
	*/
    typedef std::vector<int> bigint;
    bigint make_bigint(string const& repr)
	{
		bigint n;
		transform(repr.rbegin(), repr.rend(), back_inserter(n), [](char c){return c - '0';});
		return n;
	}

	string to_string(bigint const & n)
	{
		string str;
		transform(find_if(n.rbegin(), prev(n.rend()),
			[](char c){return c > '\0'; }), n.rend(), back_inserter(str),
			[](char c){return c + '0'; });
		return str;
	}

	bigint bigint_add(bigint const& x, bigint const& y)
	{
		bigint z(x.size() + y.size());
		for (size_t i = 0; i < x.size();i++)
		{
			for (size_t j = 0; j < y.size();j++)
			{
				z[i + j] += x[i] * y[j];
				z[i + j + 1]  += z[i + j] / 10;
				z[i + j] %= 10;
			}
		}
		return z;
	}
    string multiply(string num1, string num2) {
        if(num1=="0"||num2=="0") return "0";
        return to_string(bigint_add(make_bigint(num1),make_bigint(num2)));
    }
};