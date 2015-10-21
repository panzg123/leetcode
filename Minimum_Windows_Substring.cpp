	/*Minimum Window Substring
	双指针，动态维护一个区间。尾指针不断往后扫，当扫到有一个窗口包含了所有 T 的字符后，
	然后再收缩头指针，直到不能再收缩为止。最后记录所有可能的情况中窗口最小的
	*/
	string minWindow(string s, string t)
	{
		if (S.empty()) 
			return "";
		if (S.size() < T.size())
			return "";
		const int ASCII_MAX = 256;
		int appeared_count[ASCII_MAX];
		int expected_count[ASCII_MAX];
		fill(appeared_count, appeared_count + ASCII_MAX, 0);
		fill(expected_count, expected_count + ASCII_MAX, 0);
		for (size_t i = 0; i < T.size(); i++) 
			expected_count[T[i]]++;
		int minWidth = INT_MAX, min_start = 0; // 窗口大小，起点
		int wnd_start = 0;
		int appeared = 0; // 完整包含了一个 T
		//尾指针不断往后扫
		for (size_t wnd_end = 0; wnd_end < S.size(); wnd_end++) 
		{
			if (expected_count[S[wnd_end]] > 0) 
			{ // this char is a part of T
				appeared_count[S[wnd_end]]++;
				if (appeared_count[S[wnd_end]] <= expected_count[S[wnd_end]])
					appeared++;
			}
			if (appeared == T.size()) 
			{ // 完整包含了一个 T
				// 收缩头指针
				while (appeared_count[S[wnd_start]] > expected_count[S[wnd_start]]
					|| expected_count[S[wnd_start]] == 0) 
				{
					appeared_count[S[wnd_start]]--;
					wnd_start++;
				}
				if (minWidth > (wnd_end - wnd_start + 1))
				{
					minWidth = wnd_end - wnd_start + 1;
					min_start = wnd_start;
				}
			}
		}
		if (minWidth == INT_MAX) return "";
		else return S.substr(min_start, minWidth);
	}