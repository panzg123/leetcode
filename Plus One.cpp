class Solution {
public:
	/*Plus One 将数组代表的整数加1*/
    vector<int> plusOne(vector<int>& digits) {
             int flag = 0;
			for (auto iter = digits.rbegin(); iter != digits.rend();iter++)
			{
				int temp = (*iter + flag);
				if (iter == digits.rbegin())
				{
					temp += 1;
				}
				flag = temp / 10;
				*iter = temp % 10;
			}
			if (flag > 0)
				digits.insert(digits.begin(), flag);
			return digits;
    }
};