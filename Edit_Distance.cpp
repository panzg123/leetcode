/*Edit Distance*/
	int minDistance(string word1, string word2)
	{
		if (word1 == "" && word2=="") return 0;
		vector<vector<int>> dis(word1.size()+1, vector<int>(word2.size()+1, 0));
		for (size_t i = 0; i <= word1.size(); i++)
		{
			dis[i][0] = i;
		}
		for (size_t i = 0; i <= word2.size(); i++)
		{
			dis[0][i] = i;
		}
		for (size_t i = 1; i <= word1.size(); i++)
		{
			for (size_t j = 1; j <= word2.size(); j++)
			{
				if (word1[i - 1] == word2[j - 1])
					dis[i][j] = dis[i - 1][j - 1];
				else
				{
					int mn = min(dis[i - 1][j], dis[i][j - 1]);
					dis[i][j] = 1 + min(dis[i - 1][j - 1], mn);
				}
			}
		}
		return dis[word1.size()][word2.size()];
	}