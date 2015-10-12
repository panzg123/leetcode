class Solution {
public:
    /*Longest Substring Without Repeating Characters*/
	int lengthOfLongestSubstring(string s)
	{
		int length = s.size();
		if (length == 0) return 0;
		string temp;  //保存路径
		int max_len = 0;
		for (size_t i = 0; i < length; i++)
		{
			//查找位置
			auto find_res = find(temp.begin(), temp.end(), s[i]);
			//不重复
			if (find_res == temp.end())
			{
				temp.push_back(s[i]);
			}
			//重复，去除该重复字母之前的子串，并添加该字母追加到末尾
			else
			{
				max_len = max(max_len,(int)temp.size());
				temp.erase(temp.begin(), find_res+1);
				temp.push_back(s[i]);
			}
		}
		//字符串s本身的长度
		return max_len = max(max_len, (int)temp.size());
	}
};