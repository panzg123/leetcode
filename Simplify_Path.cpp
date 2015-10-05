class Solution
{
public:
	/*
	Given an absolute path for a file (Unix-style), simplify it.
	For example,
	path = "/home/", => "/home"
	path = "/a/./b/../../c/", => "/c"
	思路：用栈进行字符串处理
	/*simplify path*/
	string simplifyPath(string path)
	{
		vector<string> dirs; // 当做栈
		for (auto i = path.begin(); i != path.end();) 
		{
			++i;
			auto j = find(i, path.end(), '/');
			auto dir = string(i, j);
			if (!dir.empty() && dir != ".") 
			{
				// 当有连续 '///' 时， dir 为空
				if (dir == "..") 
				{
					if (!dirs.empty())
						dirs.pop_back();  /*pop_back位删除最后一个元素*/
				}
				else
					dirs.push_back(dir);
			}
			i = j;
		}
		//stringstream 用来构造格式化字符串
		stringstream out;
		if (dirs.empty()) 
		{
			out << "/";
		}
		else 
		{
			for (auto dir : dirs)
				out << '/' << dir;
		}
		return out.str();
	}
}