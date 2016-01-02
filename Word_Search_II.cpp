		/*直接dfs搜索会导致超时，要用字典树进行剪枝*/
		class solution_findwords
		{
		public:
			struct Node {
				bool end;
				Node*next[26];
				Node() { end = false; memset(next, 0, 26 * sizeof(Node*)); }
			};

			/*Word Search II,直接dfs遍历会导致超时*/
			vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
			{

				// 构造字典树
				Node *root = new Node();
				for (string w : words) {
					Node *cur = root;
					for (char c : w)
						cur = cur->next[c - 'a'] ? cur->next[c - 'a'] : cur->next[c - 'a'] = new Node();
					cur->end = true;//单词结束标记
				}

				//构造标记
				vector<vector<bool>> flag(board.size(), vector<bool>(board[0].size(), false));
				vector<string> res;

				for(int j = 0; j < board.size(); j++)
				{
					for (int i = 0; i < board[0].size(); i++)
					{
						if (root->next[board[j][i] - 'a'])
							//to do dfs
							findWords_dfs(board, root->next[board[j][i] - 'a'], flag, j, i, res, "");
					}
				}
				//按字典排序
				sort(res.begin(), res.end());
				return res;
			}
			bool findWords_dfs(vector<vector<char>>& board, Node* node, vector<vector<bool>> & flag, int index_x, int index_y,vector<string> &res,string cur_word)
			{
				cur_word += board[index_x][index_y];
				if (node->end)
				{
					auto it = find(res.begin(), res.end(), cur_word);
					if (it == res.end())
						res.push_back(cur_word);
				}

				flag[index_x][index_y] = true;
				//上
				if (index_x > 0 && flag[index_x - 1][index_y] == false && node->next[board[index_x-1][index_y]-'a'] != NULL)
				{
					findWords_dfs(board, node->next[board[index_x - 1][index_y] - 'a'], flag, index_x - 1, index_y, res, cur_word);
				}
				//下
				if (index_x < board.size() - 1 && flag[index_x + 1][index_y] == false && node->next[board[index_x + 1][index_y] - 'a'] != NULL)
				{
					findWords_dfs(board, node->next[board[index_x + 1][index_y] - 'a'], flag, index_x + 1, index_y, res, cur_word);
				}
				//左
				if (index_y>0 && flag[index_x][index_y - 1] == false && node->next[board[index_x][index_y -1] - 'a'] != NULL)
				{
					findWords_dfs(board, node->next[board[index_x][index_y -1 ] - 'a'], flag, index_x , index_y -1, res, cur_word);
				}
				//右
				if (index_y < board[0].size() - 1 && flag[index_x][index_y + 1] == false && node->next[board[index_x][index_y + 1] - 'a'] != NULL)
				{
					findWords_dfs(board, node->next[board[index_x][index_y + 1] - 'a'], flag, index_x, index_y + 1, res, cur_word);
				}
				//取消标记
				flag[index_x][index_y] = false;
				return false;
			}
		};