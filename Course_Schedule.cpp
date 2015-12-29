class Solution
{
public:
    /*Course Schedule, dfs,bfs,拓扑排序*/
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
    {
        vector<unordered_set<int>> matrix(numCourses); // 存储有向图
        for (int i = 0; i < prerequisites.size(); ++i)
            matrix[prerequisites[i].second].insert(prerequisites[i].first);

        unordered_set<int> visited; //标记节点是否依赖其他节点
        vector<bool> flag(numCourses, false); //标记节点是否被访问，因为该图存在若干独立子图
        for (int i = 0; i < numCourses; ++i)
            if (!flag[i])
                if (canFinish_DFS(matrix, visited, i, flag))
                    return false;
        return true;
    }
    bool canFinish_DFS(vector<unordered_set<int>> &matrix, unordered_set<int> &visited, int b, vector<bool> &flag)
    {
        flag[b] = true;
        visited.insert(b);
        for (auto it = matrix[b].begin(); it != matrix[b].end(); ++it) //dfs访问依赖
            if (visited.find(*it) != visited.end() || canFinish_DFS(matrix, visited, *it, flag))
                return true;
        visited.erase(b);
        return false;
    }
    /*该方法超时，原因是直接dfs，要先把无向图用vector存储*/
    bool canFinish_v2(int numCourses, vector<pair<int, int>>& prerequisites)
    {
        vector<bool> vec_flag(numCourses, false);
        vector<bool> vec_visited(numCourses, false);
        if (numCourses == 0 || numCourses == 1)
            return true;
        for (int i = 0; i < numCourses; ++i)
            if (!vec_visited[i])
                if (!canFinish_dfs_v2(numCourses, prerequisites, vec_flag,i,vec_visited))
                    return false;
        return true;
    }
    bool canFinish_dfs_v2(int numCourses, vector<pair<int, int>>& prerequisites, vector<bool>& flags, int start,vector<bool> &visited)
    {
        visited[start] = true;
        flags[start] = true;
        /*循环遍历会导致超时*/
        for (auto iter = prerequisites.begin(); iter != prerequisites.end(); iter++)
        {
            pair<int, int> var = *iter;
            if (var.first == start && flags[var.second] == true)
                return false;
            else if (var.first == start && flags[var.second] == false)
            {
                if (!canFinish_dfs_v2(numCourses, prerequisites, flags, var.second,visited))
                    return false;
            }
        }
        flags[start] = false;
        return true;
    }
    /*Course Schedule,拓扑排序*/
    bool canFinish_Top(int numCourses, vector<pair<int,int>>& prerequisites)
    {
        vector<int> in_degree(numCourses,0); //存储入度
        vector<unordered_set<int>> matrix(numCourses);//存储图
        for (int i = 0; i < prerequisites.size(); i++)
        {
            matrix[prerequisites[i].second].insert(prerequisites[i].first);
        }
        //计算入度
        for (int i = 0; i < numCourses; i++)
        {
            for (auto it = matrix[i].begin(); it != matrix[i].end(); it++)
            {
                in_degree[*it]++;
            }
        }
        stack<int> zeor_degree_stack;//存储入度为0的节点
        int count = 0;//入度0的节点计数器
        for (int i = 0; i < numCourses; i++)
        {
            if (in_degree[i] == 0)
            {
                zeor_degree_stack.push(i);
                count++; //入度为0，计数加1
            }
        }
        //循环抽取入度为0的节点
        while (!zeor_degree_stack.empty())
        {
            int top = zeor_degree_stack.top();
            zeor_degree_stack.pop();
            for (auto it = matrix[top].begin(); it != matrix[top].end(); it++)
            {
                in_degree[*it]--;
                if (in_degree[*it] == 0)
                {
                    zeor_degree_stack.push(*it);
                    count++;
                }
            }
        }
        if (count == numCourses)
            return true;
        else
            return false;
    }
};