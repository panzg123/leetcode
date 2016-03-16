//Word Pattern,https://leetcode.com/problems/word-pattern/
//hashtable
bool wordPattern(string pattern, string str)
{
    auto str_vec = split(str, " ");
    if (str_vec.size() != pattern.size())
        return false;
    unordered_map<char, string> m1;
    unordered_map<string, char> m2;
    //正向匹配
    for (int i = 0; i < pattern.size(); i++)
    {
        auto find_ret = m1.find(pattern[i]);
        if (find_ret != m1.end())
        {
            if (m1[pattern[i]] != str_vec[i])
                return false;
        }
        else
            m1[pattern[i]] = str_vec[i];
    }
    //逆向匹配
    for (int i = 0; i < pattern.size(); i++)
    {
        auto find_ret = m2.find(str_vec[i]);
        if (find_ret != m2.end())
        {
            if (m2[str_vec[i]] != pattern[i])
                return false;
        }
        else
            m2[str_vec[i]] = pattern[i];
    }
    return true;
}
//分割字符串
vector<std::string> split(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        pos = str.find(pattern, i);
        if (pos < size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}