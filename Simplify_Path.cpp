class Solution
{
public:
	/*
	Given an absolute path for a file (Unix-style), simplify it.
	For example,
	path = "/home/", => "/home"
	path = "/a/./b/../../c/", => "/c"
	˼·����ջ�����ַ�������
	/*simplify path*/
	string simplifyPath(string path)
	{
		vector<string> dirs; // ����ջ
		for (auto i = path.begin(); i != path.end();) 
		{
			++i;
			auto j = find(i, path.end(), '/');
			auto dir = string(i, j);
			if (!dir.empty() && dir != ".") 
			{
				// �������� '///' ʱ�� dir Ϊ��
				if (dir == "..") 
				{
					if (!dirs.empty())
						dirs.pop_back();  /*pop_backλɾ�����һ��Ԫ��*/
				}
				else
					dirs.push_back(dir);
			}
			i = j;
		}
		//stringstream ���������ʽ���ַ���
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