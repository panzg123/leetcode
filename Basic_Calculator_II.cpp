// Basic Calculator II,用栈
int calculate_2(string s)
{
    stack<int> ele_stack;
    int length = s.length();
    char sign = '+';
    int num = 0;
    for (int i = 0; i < length; i++)
    {
        //计算数字
        if (isdigit(s[i]))
        {
            num = num * 10 + s[i] - '0';
        }
        //加减乘除
        if (!isdigit(s[i]) && !isspace(s[i]) || i == length - 1)
        {
            if (sign == '+')
                ele_stack.push(num);
            else if (sign == '-')
                ele_stack.push(-1 * num);
            else
            {
                int value;
                if (sign == '*')
                    value = ele_stack.top()*num;
                else
                    value = ele_stack.top() / num;
                ele_stack.pop();
                ele_stack.push(value);
            }
            sign = s[i];
            num = 0;
        }
    }
    //累加
    int result = num;
    while (!ele_stack.empty())
    {
        result += ele_stack.top();
        ele_stack.pop();
    }
    return result;
}