//DFS遍历，经典操作
vector<string> addOperators(string num, int target)
{
    vector<string> res;
    if (num.empty()) return res;
    for (int i = 1; i <= num.size(); i++)
    {
        string s = num.substr(0, i);
        long cur = stol(s);
        if (to_string(cur).size() != s.size())
            continue;
        addOperators_dfs(res, num, target, s, i, cur, cur, '#');// no operator defined.
    }

    return res;

}
//dfs遍历
//result-->保存结果;cur-->目前的字符串；pos-->目前位置；cv-->目前值；pv-->前一个操作数；op-->上一个操作符
void addOperators_dfs(vector<string>& result, const string& num, const int target, string cur,int pos, const long cv, const long pv, char op)
{
    if (pos == num.size() && cv == target)
    {
        result.push_back(cur);
    }
    else
    {
        for (int i = pos + 1; i <= num.size(); i++)
        {
            string temp = num.substr(pos, i - pos);
            long value = stol(temp);
            if (to_string(value).size() != temp.size())
                continue;
            addOperators_dfs(result, num, target, cur + "+" + temp, i, cv + value, value, '+');
            addOperators_dfs(result, num, target, cur + "-" + temp, i, cv - value, value, '-');
            addOperators_dfs(result, num, target, cur + "*" + temp, i, (op == '-') ? cv + pv - pv*value : ((op == '+') ? cv - pv + pv*value : pv*value), pv*value, op);

        }
    }
}