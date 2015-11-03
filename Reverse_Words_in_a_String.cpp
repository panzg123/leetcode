		/*Reverse Words in a String 用栈*/
		void reverseWords(string &s)
		{
			stack<string> st;
			st = reverseWords_helper(s, " ");
			s.clear();
			while (!st.empty())
			{
				string str = st.top();
				if (str != "")
					s += (str + " ");
				st.pop();
			}
			if (s.size()>1)
				s.erase(s.size() - 1);
		}
		/*Reverse Words in a String 局部翻转，然后整体翻转*/
		void reverseWords_v2(string &s)
		{
			reverseWords_v2_remove_space(s); //去除多余的空白符
			if (s[0] == ' ') //去除第一个空白
				s.erase(0, 1);
			if (s == "") return; //边界直接返回
			int prev = 0;
			if(s[s.size()-1]!=' ') //如果末尾没有空格，添加一个方便处理
				s += " ";
			for (int i = 1; i < s.size();i++)
			{
				if (s[i] != ' '&& s[i - 1] == ' ') //更新起点
					prev = i;
				else if (s[i] == ' ') //遇到空格，进行翻转
					reverseWords_v2_helper(s, prev, i - 1);
			}
			if(s[s.size()-1]==' ') //去除尾部的空格
				s.erase(s.size() - 1);
			reverseWords_v2_helper(s, 0, s.size() - 1); //整体翻转
		}
		//翻转字符串，[start,end]
		void reverseWords_v2_helper(string& s, int start, int end)
		{
			while (start<end)
			{
				char temp = s[start];
				s[start] = s[end];
				s[end] = temp;
				start++;
				end--;
			}
		}
		/*去除所有多余的空白符*/
		void reverseWords_v2_remove_space(string& s)
		{
			int i = 1;
			while (i<s.size())
			{
				if (s[i - 1] == ' '&&s[i] == ' ')
					s.erase(i,1);
				else
					i++;
			}
		}
		/*字符串分割函数，结果存储在stack中*/
		stack<std::string> reverseWords_helper(std::string str, std::string pattern)
		{
			std::string::size_type pos;
			std::stack<std::string> result;
			str += pattern;//扩展字符串以方便操作
			int size = str.size();
			for (int i = 0; i < size; i++)
			{
				pos = str.find(pattern, i);
				if (pos < size)
				{
					std::string s = str.substr(i, pos - i);
					result.push(s);
					i = pos + pattern.size() - 1;
				}
			}
			return result;
		}