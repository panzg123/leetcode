//返回Num的字符串形式，num<1000
string helper(int num)
{
    vector<string> less_ten=
    { "", " One", " Two", " Three", " Four", " Five", " Six", " Seven", " Eight", " Nine" };
    vector<string> less_twenty =
    { " Ten", " Eleven", " Twelve", " Thirteen", " Fourteen", " Fifteen", " Sixteen", " Seventeen", " Eighteen", " Nineteen" };
    vector<string> less_hundred =
    { "", "", " Twenty", " Thirty", " Forty", " Fifty", " Sixty", " Seventy", " Eighty", " Ninety" };

    string s;

    if (num != 0)
    {
        //获取个十百位
        int hundred = num / 100;
        num %= 100;
        int tenth = num / 10;
        int single = num % 10;

        if (hundred) s = s + less_ten[hundred] + " Hundred";

        if (tenth)
        {
            if (tenth == 1)
            {
                //10-19之间的特殊数字
                s += less_twenty[single];
                return s;
            }
            else  s += less_hundred[tenth];

        }
        if (single) s += less_ten[single];
    }
    return s;
}
//Integer to English Words,https://leetcode.com/problems/integer-to-english-words/
//字符串处理，参考：https://leetcode.com/discuss/55254/c-solution-4ms
string numberToWords(int num)
{
    if (num == 0)
        return "Zero";
    //第一个元素起到占位的作用
    vector<string> unit=
    { "", " Thousand", " Million", " Billion" };
    int parts[4] = { 0 };
    for (int i = 0; i < 4; ++i)
    {
        parts[i] = num % 1000;
        num /= 1000;
    }
    string s;
    for (int i = 0; i < 4; ++i)
    {
        if (parts[i] == 0) continue;
        s = helper(parts[i]) + unit[i] + s;
    }
    //删除首部的空格符
    s.erase(s.begin());
    return s;
}