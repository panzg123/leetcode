//二叉树性质，n个树节点，则n+1空节点，先序遍历的最后一个节点为空节点
		class isValidSerializationSolution 
		{
		public:
			bool isValidSerialization(string preorder) 
			{
				istringstream s(preorder);
				int node_c = 0, null_c = 0;
				string cur;
				while (getline(s, cur, ',')) 
				{
					if (cur == "#") 
						++null_c;
					else
						++node_c;
					if (s.good() && null_c == node_c + 1) 
						return false;
				}
				return null_c == node_c + 1;
			}
		};