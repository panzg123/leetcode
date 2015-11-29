class Solution
{
public:
    /*Isomorphic Strings 分别记录s到t,t到s的单词映射，32ms*/
    bool isIsomorphic(string s, string t)
    {
        if (s.length() != t.length()) return false;
        //记录s到t的映射
        unordered_map<char, char> mp;
        for (int i = 0; i < s.length(); ++i)
        {
            if (mp.find(s[i]) == mp.end())
                mp[s[i]] = t[i];
            else if (mp[s[i]] != t[i])
                return false;
        }
        //记录t到s的映射
        mp.clear();
        for (int i = 0; i < s.length(); ++i)
        {
            if (mp.find(t[i]) == mp.end())
                mp[t[i]] = s[i];
            else if (mp[t[i]] != s[i])
                return false;
        }
        return true;
    }
    /*Isomorphic Strings 分别记录s到t,t到s的单词映射,用数组，8ms*/
    bool isIsomorphic_v2(string s, string t)
    {
        if (s.length() != t.length())
            return false;
        int map1[256], map2[256];
        fill_n(map1, 256, 0);
        fill_n(map2, 256, 0);
        for (int i = 0; i < s.length(); i++)
        {
            //s到t的映射检查
            if (map1[s[i]] == 0)
                map1[s[i]] = t[i];
            else if (map1[s[i]] != t[i])
                return false;
            //t到s的映射检查
            if (map2[t[i]] == 0)
                map2[t[i]] = s[i];
            else if (map2[t[i]] != s[i])
                return false;
        }
        return true;
    }
};