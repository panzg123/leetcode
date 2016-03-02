//Number of Digit One,https://leetcode.com/problems/number-of-digit-one/
//直接遍历，超时
int countDigitOne(int n)
{
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        int a = i;
        while (a)
        {
            if (a%10 == 1)
                count++;
            a /= 10;
        }
    }
    return count;
}
//数学题，找规律，《数学之美》，链接：http://www.cppblog.com/myjfm/archive/2012/09/04/189444.html
int countDigitOne_v2(int n)
{
    long high = 0;
    long low = 0;
    long cur = 0;
    long factor = 1;
    long count = 0;
    while (n>=factor)
    {
        high = n / (factor * 10);
        cur = (n / factor) % 10;
        low = n % factor;
        if (cur == 0)
            count += high*factor;
        else if (cur == 1)
            count += high*factor + 1 + low;
        else
            count += (high + 1)*factor;

        factor *= 10;
    }
    return count;
}