/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    /*Clone Graph BFS，时间复杂度 O(n)，空间复杂度 O(n)*/
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
	{
		if (node == nullptr) return nullptr;
		unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> copied;
		queue<UndirectedGraphNode*> q;
		q.push(node);
		copied[node] = new UndirectedGraphNode(node->label);
		while (!q.empty())
		{
			UndirectedGraphNode *cur = q.front();
			q.pop();
			for (auto nbr : cur->neighbors)
			{
				//是否存在
				if (copied.find(nbr) != copied.end())
				{
					copied[cur]->neighbors.push_back(copied[nbr]);
				}
				else
				{
					UndirectedGraphNode * new_node = new UndirectedGraphNode(nbr->label);
					copied[nbr] = new_node;
					copied[cur]->neighbors.push_back(new_node);
					q.push(nbr);
				}
			}
		}
		return copied[node];
	}
	/*Clone Graph DFS,时间复杂度 O(n)，空间复杂度 O(n)*/
	UndirectedGraphNode *cloneGraph_v2(const UndirectedGraphNode *node)
	{
		if (node == nullptr) return nullptr;
		// key is original node， value is copied node
		unordered_map<const UndirectedGraphNode *,
			UndirectedGraphNode *> copied;
		cloneGraph_dfs(node, copied);
		return copied[node];
	}
	// DFS辅助函数
	static UndirectedGraphNode* cloneGraph_dfs(const UndirectedGraphNode *node,
		unordered_map<const UndirectedGraphNode *,
		UndirectedGraphNode *> &copied)
	{
		// a copy already exists
		if (copied.find(node) != copied.end()) return copied[node];
		UndirectedGraphNode *new_node = new UndirectedGraphNode(node->label);
		copied[node] = new_node;
		for (auto nbr : node->neighbors)
			new_node->neighbors.push_back(cloneGraph_dfs(nbr, copied));
		return new_node;
	}
};