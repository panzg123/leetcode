class Solution
{
public:
    //Shortest Palindrome,直接循环判断，超时
    string shortestPalindrome(string s)
    {
        string temp;
        int index = s.length();
        //从字符串末尾查找，最长的回文串
        while (index>1)
        {
            temp.assign(s, 0, index);
            if (is_palindrome(temp))
                break;
            else
                index--;
        }
        //找到最长回文串，构造结果
        if (index != s.length())
            temp.assign(s, index, string::npos);
        else
            return s;
        reverse(temp.begin(), temp.end());
        temp += s;
        return temp;
    }
    //判断是否回文
    bool is_palindrome(string s)
    {
        if (s.length() == 1)
            return true;
        int i=0,j=s.length()-1;
        while (i<j)
        {
            if (s[i] != s[j])
                return false;
            else
            {
                i++;
                j--;
            }
        }
        return true;
    }
    //Shortest Palindrome,kmp匹配法，具体可以参考讲解：https://leetcode.com/discuss/64309/clean-kmp-solution-with-super-detailed-explanation
    string shortestPalindrome_kmp(string s)
    {
        //先构造字符串:s+"#"+reverse(s),比如catacb的构造结果为：catacb # bcatac，保存到temp
        string temp = s;
        string str_res;
        temp += "#";
        string temp2 = s;
        reverse(temp2.begin(), temp2.end());
        temp += temp2;
        //获取kmp表
        vector<int> res(temp.size(), 0);
        kmp_get_next(temp, res);
        //取得最kmp末尾的值
        int index = res[temp.size() - 1];
        if (index != s.length()-1)
            str_res.assign(s, index+1, string::npos);
        else
            return s;
        reverse(str_res.begin(), str_res.end());
        //存储结果
        str_res += s;
        return str_res;
    }
    //kmp table
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