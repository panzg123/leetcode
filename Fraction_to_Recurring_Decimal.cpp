//string fractionToDecimal(int numerator, int denominator)
//思路是用unordered_map来记录出现的数，如果重复出现，则是循环
string fractionToDecimal(long long numerator, long long denominator)
{
    string result;
    if (numerator == 0)
        return "0";
    if (denominator == 0)
        return "";
    //异号
    if ((numerator < 0) ^ (denominator < 0))
        result += "-";
    long long a = abs((long long)numerator);
    long long b = abs((long long)denominator);
    //求得整数部分
    result += to_string(abs(a) / abs(b));
    if (numerator%denominator == 0)
        return result;
    result += ".";
    //求小数部分
    unordered_map<int, int> map;
    for (long long r = a%b; r; r %= b)
    {
        if (map.count(r) > 0)
        {
            //在数r位置的前面插入'('
            result.insert(map[r], 1, '(');
            result += ")";
            break;
        }
        //保存数r出现的位置
        map[r] = result.size();
        r *= 10;
        result += to_string(r / b);
    }
    return result;
}