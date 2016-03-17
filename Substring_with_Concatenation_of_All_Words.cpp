class Solution {
public:
	/*Substring with Concatenation of All Word 
	时间复杂度 O(n)，空间复杂度 O(m)*/
	vector<int> result;

	if (words.empty() || words[0].empty())  //字符串数组为空或者单词为空，直接返回
	{
		return result;
	}

	int num = words.size();                 //num记录单词的个数
	int len = words[0].size();              //记录单词的长度
	unordered_map<string, int> counter;
	unordered_map<string, int> appear;

	for (int i = 0; i < num; ++i)           //将每个单词加入到：单词-个数映射中
	{
		++counter[words[i]];
	}

	for (int i = 0; i < len; ++i)
	{
		appear.clear();                     //清空记录单词映射关系的map
		int start = i, count = 0;           //start:保存符合要求的字串的起始位置，count:记录单词的个数

		for (int j = i; j + len <= s.size(); j += len)
		{
			string word = s.substr(j, len);
			if (counter.find(word) == counter.end())   //当前单词不在单词数组中
			{
				appear.clear();                        //清空appear映射
				start = j + len;                       //开始位置指向下一个单词的位置
				count = 0;
				continue;
			}

			++appear[word];                            //单词映射的个数加1
			++count;                                   //总的单词出现次数加1
			if (appear[word] > counter[word])          //如果某个出现的次数大于单词数组中的个数，
			{	                                       //从appear中删除从start到该单词(含)第一次出现之间的所有单词
				while (appear[word] > counter[word])
				{
					--appear[s.substr(start, len)];
					--count;                          //单词计数和起始位置做相应的调整
					start += len;
				}
			}
			else if (count == words.size())           //如果count等于单词数组的总个数，将起始位置添加到结果中
			{                                         //appear、count和start做相应的调整
				result.push_back(start);
				--appear[s.substr(start, len)];
				--count;
				start += len;
			}
		}
	}
	return result;
};