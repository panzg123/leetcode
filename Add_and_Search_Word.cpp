		/*Add and Search Word，遍历匹配，超时*/
		class WordDictionary {
		public:

			vector<string> words;

			// Adds a word into the data structure.
			void addWord(string word) {
				words.push_back(word);
			}

			// Returns if the word is in the data structure. A word could
			// contain the dot character '.' to represent any one letter.
			bool search(string word) {
				for (auto it = words.begin(); it != words.end(); it++)
				{
					if (match(*it, word))
						return true;
				}
				return false;
			}
			bool match(string dst, string src)
			{
				if (dst.length() != src.length())
					return false;
				int count_dot = 0;
				for (int i = 0; i < src.length(); i++)
				{
					if (src[i] == '.')
					{
						count_dot++;
						if (count_dot>2)
							return false;
					}
					else if (src[i] != dst[i])
						return false;
					else
						count_dot = 0;
				}
				return true;
			}
		};
		/*Add and Search Word ，字典树*/
		class WordDictionary_v2 {
		public:
			struct Node {
				bool end;
				Node *nodes[26];
				Node() {
					end = false;
					memset(nodes, 0, 26 * sizeof(Node*));
				}
			} *root;

			WordDictionary_v2() {
				root = new Node(), root->end = true;
			}

			void addWord(string word) {
				Node *cur = root;
				for (char c : word) {
					Node*& n = cur->nodes[c - 'a'];//watch out,the "&"
					cur = n ? n : (n = new Node());
				}
				cur->end = true;
			}

			bool search(string word) {
				return find(word, 0, root);
			}

			//dfs匹配
			bool find(string& word, int pos, Node *from) {
				if (pos == word.length())
					return from->end;

				if (word[pos] == '.')
					for (auto& n : from->nodes)
						if (n && find(word, pos + 1, n))
							return true;
				else
					return from->nodes[word[pos] - 'a'] ? find(word, pos + 1, from->nodes[word[pos] - 'a']) : false;

				return false;
			}
		};