		/*Excel Sheet Column Number*/
		int titleToNumber(string s)
		{
			int length = s.size();
			int result = 0;
			for (int i = 0; i < length;i++)
			{
				result = 26*result+s[i]-'A'+1;
			}
			return result;
		}