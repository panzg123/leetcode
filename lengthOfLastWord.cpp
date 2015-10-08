class Solution
{
public:
    string& trim(string &s)
    {
        if (s.empty())
            {
                return s;
            }
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
        return s;
    }
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
    int lengthOfLastWord(string s)
    {
        trim(s);
        vector<string> result = split(s," ");
        if (result.size() == 0) return 0;
        else return result[result.size() - 1].size();
    }
    int lengthOfLastWord_v2(string s)
    {
        int len = s.length();
        int count = 0;
        for(int i = len - 1; i >= 0; i--)
            {
                if(s[i] == ' ' && count) break;
                if(s[i] != ' ') count++;
            }
        return count;
    }
}