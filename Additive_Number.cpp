//https://leetcode.com/problems/additive-number/
//解法，递归
bool isAdditiveNumber(string num)
{
    for (int i = 1; i <= num.size() / 2; i++)
    {
        for (int j = 1; j <= (num.size() - i) / 2; j++)
        {
            if (i >= 2 && num[0] == '0' || j >= 2 && num[i] == '0' || num[i + j] == '0')
                continue;
            if (isAdditiveNumber_helper(stol(num.substr(0, i)), stol(num.substr(i, j)), num.substr(i + j)))
                return true;
        }
    }
    return false;
}
bool isAdditiveNumber_helper(long num1, long num2, string num)
{
    if (num.size() > 1 && num[0] == '0') return false;
    long sum = num1 + num2, numI = stol(num);
    long len = static_cast<long>(log10(sum)) + 1;
    if (numI == sum) return true;
    if (numI < sum || sum != stol(num.substr(0, len))) return false;
    else return isAdditiveNumber_helper(num2, sum, num.substr(len));
}