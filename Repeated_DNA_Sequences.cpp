class Solution
{
public:
	/*Repeated DNA Sequences ，unordered_map*/
    vector<string> findRepeatedDnaSequences(string s)
    {
        unordered_map<string, int> count;
        vector<string> result;
        if (s.size() < 11) return result;
        for (size_t i = 0; i <= s.size()-10; i++)
        {
            string temp(s, i, 10);
            auto find_res = count.find(temp);
            if (find_res != count.end() && find_res->second == 1)
            {
                result.push_back(temp);
                find_res->second++;
            }
            else
                count[temp]++;
        }
        return result;
    }
    /*Repeated DNA Sequences 暴力破解法*/
    vector<string> findRepeatedDnaSequences(string s)
    {
        int i = 0, j = 0;
        int length = s.size();
        vector<string> result;
        for (i = 0; i < length - 20; i++)
        {
            for (j = i + 10; j < length - 10; j++)
            {
                int index = 0;
                while (index<10 && s[i+index]==s[j+index])
                {
                    index++;
                }
                if (index == 10)
                {
                    result.push_back(string(s, i,10));
                }
            }
        }
        return result;
    }
    /*Repeated DNA Sequences 位运算*/
    vector<string> findRepeatedDnaSequences_v2(string s)
    {
        char  hashMap[1048576] = { 0 };
        vector<string> ans;
        int len = s.size(), hashNum = 0;
        if (len < 11) return ans;
        for (int i = 0; i < 9; ++i)
            hashNum = hashNum << 2 | (s[i] - 'A' + 1) % 5;
        for (int i = 9; i < len; ++i)
            if (hashMap[hashNum = (hashNum << 2 | (s[i] - 'A' + 1) % 5) & 0xfffff]++ == 1)
                ans.push_back(s.substr(i - 9, 10));
        return ans;
    }
};