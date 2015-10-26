class Solution {
public:
	/*Substring with Concatenation of All Word 
	时间复杂度 O(n*m)，空间复杂度 O(m)*/
    vector<int> findSubstring(string s, vector<string>& dict)
	{
		size_t wordLength = dict.front().length();
		size_t catLength = wordLength*dict.size(); //计算dict的总长度

		vector<int> result; 
		if (s.length() < catLength) return result;
		unordered_map<string, int> wordCount; //将dict表示为map键值对形式
 		for (auto const & word:dict)
		{
			++wordCount[word];
		}
		for (auto i = begin(s);i<=prev(end(s),catLength);++i)
		{
			//在[i,i+catLength)的范围内判断是否符合要求
			unordered_map<string, int> unused(wordCount);
			for (auto j = i;j!=next(i,catLength);j+=wordLength)
			{
				auto pos = unused.find(string(j, next(j, wordLength)));

				if (pos == unused.end() || pos -> second == 0) 
					break;
				//减少unused次数
				if (--pos->second == 0) 
					unused.erase(pos);
			}
			//正好全部包含
			if (unused.size() == 0)
				result.push_back(distance(begin(s), i));
		}
		return result;
	}
};