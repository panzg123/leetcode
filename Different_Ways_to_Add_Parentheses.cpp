class Solution
{
public:
    /*Different Ways to Add Parentheses,递归*/
    vector<int> diffWaysToCompute(string input)
    {
        int length = input.size();
        vector<int> res;
        for (int i = 0; i < length; i++)
        {
            char c = input[i];
            //操作符
            if (ispunct(c))
            {
                vector<int> l_res = diffWaysToCompute(input.substr(0, i)); //左端结果
                vector<int> r_res = diffWaysToCompute(input.substr(i + 1)); //右端结果
                //组合
                for (int j = 0; j < l_res.size(); j++)
                {
                    for (int k = 0; k < r_res.size(); k++)
                    {
                        switch (c)
                        {
                        case '+':
                            res.push_back(l_res[j] + r_res[k]);
                            break;
                        case '-':
                            res.push_back(l_res[j] - r_res[k]);
                            break;
                        case '*':
                            res.push_back(l_res[j] * r_res[k]);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }

        }
        //字符串转化为数字
        if (res.empty())
            res.push_back(stoi(input));
        return res;
    }
};