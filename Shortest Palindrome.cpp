class Solution
{
public:
    string shortestPalindrome(string s)
    {
        string temp = s;
        string str_res;
        temp += "#";
        string temp2 = s;
        reverse(temp2.begin(), temp2.end());
        temp += temp2;

        vector<int> res(temp.size(), 0);
        kmp_get_next(temp, res);

        int index = res[temp.size() - 1];
        if (index != s.length()-1)
            str_res.assign(s, index+1, string::npos);
        else
            return s;
        reverse(str_res.begin(), str_res.end());
        str_res += s;
        return str_res;
    }
    void kmp_get_next(string s, vector<int>& next)
    {
        int length = s.size();
        int j = 1, k = 0;
        next[0] = -1;
        next[1] = 0;
        while (j<length-1)
        {
            if (s[j] == s[k])
            {
                j++;
                k++;
                next[j] = k;
            }
            else if (k == 0)
            {
                j++;
                next[j] = 0;
            }
            else
                k = next[k];
        }
    }
};