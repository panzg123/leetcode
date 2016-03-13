		//H-Index,https://leetcode.com/problems/h-index/
		//直接先排序
		int hIndex(vector<int>& citations) 
		{
			if (citations.empty())
				return 0;
			sort(citations.begin(), citations.end());
			int n = citations.size();
			int i = 0;
			while (i < n && citations[i] < (n - i)) 
				i++;
			return n - i;
		}
		//H-Index,https://leetcode.com/problems/h-index/
		//hashtable，时间复杂度为O(N)
		int hIndex_v2(vector<int>& citations) 
		{
			if (citations.empty())
				return 0;
			int n = citations.size();
			vector<int> hash(n + 1, 0);
			for (int i = 0; i < n; ++i)
			{
				if (citations[i] >= n)
					hash[n]++;
				else
					hash[citations[i]]++;
			}
			int paper = 0;
			for (int i = n; i >= 0; --i)
			{
				paper += hash[i];
				if (paper >= i)
					return i;
			}
		}