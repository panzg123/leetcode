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
	
	//时间复杂度 O(n*m)，空间复杂度 O(n+m)
	string multiply(string num1, string num2) {
		if (num1 == "0" || num2 == "0" || num1.empty() || num2.empty())    //判空、判0
			return "0";
		
		vector<int> multiplyNum(num1.size() + num2.size(), 0);             //存储对应的乘积，初始值为0
		for (int i = 0; i < num1.size(); ++i)
		{
			for (int j = 0; j < num2.size(); ++j)
			{
				multiplyNum[i + j] +=                                      //各个位的相乘结果对应累加起来
					(num1[num1.size() - 1 - i] - '0')*(num2[num2.size() - 1 - j] - '0');
			}
		}

		int carry = 0, tmp = 0;
		for (int i = 0; i < multiplyNum.size(); ++i)                       //整理各位的乘积
		{
			tmp = multiplyNum[i] + carry;
			multiplyNum[i] = tmp % 10;
			carry = tmp / 10;
		}

		int pos = multiplyNum.size();
		while (--pos >= 0 && multiplyNum[pos] == 0);                       //从左到右，查找第一个不为0的位置
		string result = "";
		while (pos>=0)                                                     //将int型数组转为字符串
		{
			result += multiplyNum[pos] + '0';
			--pos;
		}

		return result;
	}

};