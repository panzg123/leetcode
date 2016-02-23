//224. Basic Calculator
//将所有括号展开，用sign_vec来记录符号变换，result记录计算结果
int calculate(string s)
{
    vector<int> sign_vec = {1};
    int sign = 1;
    int num = 0;
    int result = 0;
    int length = s.length();
    for (int i = 0; i < length; i++)
    {
        if (s[i] == ' ')
        {
            continue;
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            num = num * 10 + s[i] - '0';
            continue;
        }
        else if (s[i] == '(')
        {
            result += num*sign*sign_vec.back();
            sign_vec.push_back(sign*sign_vec.back());
            num = 0;
            sign = 1;

        }
        else if (s[i] == ')')
        {
            result += num*sign*sign_vec.back();
            num = 0;
            sign_vec.pop_back();
        }
        else if (s[i] == '+')
        {
            result += num*sign*sign_vec.back();
            sign = 1;
            num = 0;
        }
        else if (s[i] == '-')
        {
            result += num*sign*sign_vec.back();
            sign = -1;
            num = 0;
        }
    }
    result += num*sign*sign_vec.back();
    return result;
}